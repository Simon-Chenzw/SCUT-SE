from typing import Tuple

from sqlalchemy import and_

from ..data import db
from ..typing.vote import table, VoteStatus


async def vote_count(aid: int) -> Tuple[int, int]:
    up = await db.fetch_val(
        table.count(and_(
            table.c.aid == aid,
            table.c.status == VoteStatus.up,
        )))
    down = await db.fetch_val(
        table.count(
            and_(
                table.c.aid == aid,
                table.c.status == VoteStatus.down,
            )))
    return up, down


async def vote_stat(aid: int, uid: int) -> VoteStatus:
    cur_stat = await db.fetch_val(
        table.select(and_(
            table.c.aid == aid,
            table.c.uid == uid,
        )).with_only_columns([table.c.status]))
    return cur_stat or VoteStatus.neither