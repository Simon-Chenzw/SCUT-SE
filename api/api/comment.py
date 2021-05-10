from typing import List, Optional

from fastapi import Depends, HTTPException, status
from sqlalchemy import and_

from ..app import app
from ..data import db
from ..depends.answer import get_answer
from ..depends.user import get_full_user, login_user
from ..typing.answer import AnswerInDB
from ..typing.comment import Comment, CommentCreate, CommentInDB, table
from ..typing.user import UserInDB


async def get_comment(cid: int) -> CommentInDB:
    obj = await db.fetch_one(table.select(table.c.cid == cid))
    if obj:
        return CommentInDB.parse_obj(obj)
    else:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"cid {cid} does not exist",
        )


@app.post("/comment/create", tags=['comment'])
async def comment_create(
        com: CommentCreate,
        answer: AnswerInDB = Depends(get_answer),
        user: UserInDB = Depends(login_user),
):
    await db.execute(
        table.insert(
            CommentInDB(
                cid=0,
                aid=answer.aid,
                uid=user.uid,
                text=com.text,
            ).dict()))
    return {'msg': 'Comment create successfully'}


@app.post("/comment/info", response_model=Comment, tags=['comment'])
async def comment_info(com: CommentInDB = Depends(get_comment)) -> Comment:
    user = await get_full_user(com.uid)
    return Comment.parse_obj({
        **com.dict(),
        'user': user.dict(),
    })


@app.get("/comment/list", response_model=List[Comment], tags=['comment'])
async def comment_list(
    aid: Optional[int] = None,
    last_cid: Optional[int] = None,
    limit=10,
) -> List[Comment]:
    sel = table.select().order_by(table.c.cid).limit(limit)
    if aid:
        sel = sel.where(table.c.aid == aid)
    if isinstance(last_cid, int):
        sel = sel.where(table.c.cid <= last_cid)
    return [
        await comment_info(CommentInDB.parse_obj(obj))
        for obj in await db.fetch_all(sel)
    ]
