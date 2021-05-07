from fastapi import HTTPException, status

from ..data import db
from ..typing.answer import AnswerInDB, table


async def get_answer(aid: int) -> AnswerInDB:
    obj = await db.fetch_one(table.select(table.c.aid == aid))
    if not obj:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"aid {aid} does not exist",
        )
    return AnswerInDB.parse_obj(obj)
