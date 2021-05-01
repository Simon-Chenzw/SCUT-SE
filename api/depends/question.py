from fastapi import HTTPException, status

from ..data import db
from ..typing.question import Question, table


async def get_question(qid: int) -> Question:
    obj = await db.fetch_one(table.select(table.c.qid == qid))
    if obj is None:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="qid does not exist",
        )
    return Question.parse_obj(obj)