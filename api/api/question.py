from typing import Optional

from fastapi import Depends, HTTPException, status

from ..app import app
from ..data import db
from ..typing.question import Question, table, QuestionCreate
from ..typing.user import UserInDB
from ..depends.user import login_user
from ..depends.question import get_question


@app.post("/question/create", tags=['question'])
async def question_create(
        que: QuestionCreate,
        user: UserInDB = Depends(login_user),
):
    obj = Question(
        qid=0,
        title=que.title,
        desc=que.desc,
    )
    if (await db.fetch_val(table.count(table.c.title == que.title))) == 0:
        await db.execute(table.insert(obj.dict()))
        return {'msg': 'Question created successfully'}
    else:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="title already exists",
        )


@app.get("/question/info", response_model=Question, tags=['question'])
async def question_info(que: Question = Depends(get_question)) -> Question:
    return que


@app.post("/question/modify", tags=['question'])
async def question_modify(
        mod: QuestionCreate,
        que: Question = Depends(get_question),
        user: UserInDB = Depends(login_user),
):
    await db.execute(
        table.update(table.c.qid == que.qid, {
            'title': mod.title,
            'desc': mod.desc,
        }))
    return {'msg': 'Question modify successfully'}
