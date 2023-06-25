#!python3.10
import json
import logging
import os
import sys
from typing import Any, Dict, Optional
from urllib import request

logging.basicConfig(
    level=logging.DEBUG,
    format='%(levelname)-8s| %(message)s',
)
logger = logging.getLogger(__name__)


class QQbot:
    def __init__(
        self,
        qid: int,
        socket: str,
        verifyKey: str,
    ) -> None:
        self.qid = qid
        self.socket = socket
        self.verifyKey = verifyKey

    def apiPost(self, interface: str, **data: Any) -> Dict[str, Any]:
        try:
            req = request.Request(
                f"https://{self.socket}/{interface}",
                data=json.dumps(data).encode('utf8'),
                headers={'content-type': 'application/json'},
            )
            resp = request.urlopen(req)
            res: Dict[str, Any] = json.loads(resp.read().decode('utf8'))

            if res['code']:
                code = res['code']
                msg = res.get('msg', 'unknown')
                logger.error(f'{interface} failed: {code=} {msg=}')
                raise RuntimeError('return code is non-zero')
        except Exception as err:
            logger.error(f'{interface} failed: {err=}')
            raise
        logger.info(f"{interface} succeeded: {res=}")
        return res

    def __enter__(self) -> 'QQbot':
        # auth
        self.session = self.apiPost(
            'verify',
            verifyKey=self.verifyKey,
        )['session']
        # verify
        self.apiPost(
            'bind',
            sessionKey=self.session,
            qq=self.qid,
        )

        return self

    def __exit__(self, exc_type, exc_value, traceback) -> bool:
        try:
            self.apiPost('release', sessionKey=self.session, qq=self.qid)
        except RuntimeError:
            # https://github.com/project-mirai/mirai-api-http/issues/358
            pass
        return False

    def send(
        self,
        target: int,
        message: str,
        method: str = "sendFriendMessage",
    ) -> None:
        self.apiPost(
            method,
            target=target,
            messageChain=[{
                'type': 'Plain',
                'text': message,
            }],
            sessionKey=self.session,
        )


args = os.getenv('MADOKA_ARGS')
if args:
    qid, target, socket, verifyKey = args.split()
else:
    logger.error("can't get environment variables MADOKA_ARGS")
    exit(1)

with QQbot(
        qid=int(qid),
        socket=socket,
        verifyKey=verifyKey,
) as bot:
    message = sys.stdin.read()
    if message.endswith('\n'): message = message[:-1]
    bot.send(int(target), message, method='sendGroupMessage')