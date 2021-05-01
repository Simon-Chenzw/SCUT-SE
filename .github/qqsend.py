import json
import logging
import os
import sys
from typing import Any, Dict
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
        adminQid: int,
        socket: str,
        authKey: str,
    ) -> None:
        self.qid = qid
        self.adminQid = adminQid
        self.socket = socket
        self.authKey = authKey

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
        self.session = self.apiPost('auth', authKey=self.authKey)['session']
        # verify
        self.apiPost('verify', sessionKey=self.session, qq=self.qid)

        return self

    def __exit__(self, exc_type, exc_value, traceback) -> bool:
        self.apiPost('release', sessionKey=self.session, qq=self.qid)
        return False

    def send(self, message: str) -> None:
        self.apiPost(
            'sendFriendMessage',
            target=self.adminQid,
            messageChain=[{
                'type': 'Plain',
                'text': message,
            }],
            sessionKey=self.session,
        )


args = os.getenv('MADOKA_ARGS')
if args:
    qid, adminQid, socket, authKey = args.split()
else:
    logger.error("can't get environment variables MADOKA_ARGS")
    exit(1)

with QQbot(
        qid=int(qid),
        adminQid=int(adminQid),
        socket=socket,
        authKey=authKey,
) as bot:
    message = sys.stdin.read()
    if message.endswith('\n'): message = message[:-1]
    bot.send(message)
