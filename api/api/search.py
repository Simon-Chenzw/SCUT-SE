from typing import List, Optional

from fastapi import Depends
from sqlalchemy import or_

from ..app import app
from ..data import db
from ..depends.answer import get_full_answer
from ..depends.user import login_user_possible
from ..typing import question
from ..typing.answer import Answer, AnswerInDB, table
from ..typing.user import UserInDB


@app.get(
    "/answer/search",
    response_model=List[Answer],
    tags=['answer'],
)
async def answer_search(
        s: str,
        offset: int = 0,
        limit: int = 10,
        user: Optional[UserInDB] = Depends(login_user_possible),
) -> List[Answer]:
    sel = table.join(
        question.table,
        table.c.qid == question.table.c.qid,
    ).select(
        or_(
            table.c.text.ilike(f"%{s}%"),
            question.table.c.title.ilike(f"%{s}%"),
            question.table.c.desc.ilike(f"%{s}%"),
        )).with_only_columns(table.c).order_by(
            table.c.aid).offset(offset).limit(limit)
    return [
        await get_full_answer(AnswerInDB.parse_obj(obj), user)
        for obj in await db.fetch_all(sel)
    ]
