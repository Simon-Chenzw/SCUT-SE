from typing import List, Optional

from fastapi import Depends, HTTPException, status

from ..app import app
from ..data import db
from ..depends.question import get_question
from ..depends.user import login_user
from ..typing.question import Question, QuestionCreate, table
from ..typing.user import UserInDB


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


@app.get("/question/list", response_model=List[Question], tags=['question'])
async def question_list(
    last_qid: Optional[int] = None,
    limit: int = 10,
) -> List[Question]:
    sel = table.select().order_by(table.c.qid).limit(limit)
    if isinstance(last_qid, int):
        sel = sel.where(table.c.qid <= last_qid)
    return [Question.parse_obj(obj) for obj in await db.fetch_all(sel)]
