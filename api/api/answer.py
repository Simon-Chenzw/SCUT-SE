from typing import List, Optional

from fastapi import Depends, HTTPException, status
from sqlalchemy import and_

from ..app import app
from ..data import db
from ..depends.answer import get_answer, get_full_answer
from ..depends.question import get_question
from ..depends.user import get_full_user, login_user, login_user_possible
from ..depends.vote import vote_count, vote_stat
from ..typing import vote
from ..typing.answer import Answer, AnswerCreate, AnswerInDB, table
from ..typing.question import Question
from ..typing.user import UserInDB


@app.post("/answer/create", tags=['answer'])
async def answer_create(
        answer: AnswerCreate,
        que: Question = Depends(get_question),
        user: UserInDB = Depends(login_user),
):
    if not answer.text:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"text cannot be empty",
        )
    if await db.fetch_val(
            table.count(and_(
                table.c.uid == user.uid,
                table.c.qid == que.qid,
            ))):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"one can not create two answer in same question",
        )
    obj = AnswerInDB(
        aid=0,
        qid=que.qid,
        uid=user.uid,
        text=answer.text,
    )
    await db.execute(table.insert(obj.dict()))
    return {'msg': 'Answer create successfully'}


@app.get("/answer/info", response_model=Answer, tags=['answer'])
async def answer_info(
        answer: AnswerInDB = Depends(get_answer),
        user: Optional[UserInDB] = Depends(login_user_possible),
) -> Answer:
    return await get_full_answer(answer, user)


@app.post("/answer/modify", tags=['answer'])
async def answer_modify(
        mod: AnswerCreate,
        answer: AnswerInDB = Depends(get_answer),
        user: UserInDB = Depends(login_user),
):
    if answer.uid != user.uid:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"Cannot change answers that were not created by yourself",
        )

    await db.execute(
        table.update(
            table.c.aid == answer.aid,
            {'text': mod.text},
        ))
    return {'msg': 'Answer modify successfully'}


@app.get("/answer/list", response_model=List[Answer], tags=['answer'])
async def answer_list(
        last_aid: Optional[int] = None,
        qid: Optional[int] = None,
        limit: int = 10,
        user: Optional[UserInDB] = Depends(login_user_possible),
) -> List[Answer]:
    sel = table.select().order_by(-table.c.aid).limit(limit)
    if qid:
        que = await get_question(qid)
        sel = sel.where(table.c.qid == que.qid)
    if isinstance(last_aid, int):
        sel = sel.where(table.c.aid <= last_aid)
    return [
        await get_full_answer(AnswerInDB.parse_obj(obj), user)
        for obj in await db.fetch_all(sel)
    ]
