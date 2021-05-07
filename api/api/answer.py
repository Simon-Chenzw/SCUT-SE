from typing import Mapping, Optional

from fastapi import Depends, HTTPException, status
from sqlalchemy import and_

from ..app import app
from ..data import db
from ..depends.question import get_question
from ..depends.user import login_user, login_user_possible, get_full_user
from ..typing import comment, vote
from ..typing.answer import Answer, AnswerInDB, table, AnswerCreate
from ..typing.comment import Comment, CommentInDB, CommentCreate
from ..typing.question import Question
from ..typing.user import UserInDB


async def get_answer(aid: int) -> AnswerInDB:
    obj = await db.fetch_one(table.select(table.c.aid == aid))
    if not obj:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"aid {aid} does not exist",
        )
    return AnswerInDB.parse_obj(obj)


@app.post("/answer/create", tags=['answer'])
async def create_answer(
        answer: AnswerCreate,
        que: Question = Depends(get_question),
        user: UserInDB = Depends(login_user),
):
    if not answer.text:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"text cannot be empty",
        )
    if db.fetch_val(
            table.count(and_(
                table.c.uid == user.uid,
                table.c.qid == que.qid,
            ))):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"one can two answer in same question",
        )
    obj = AnswerInDB(
        aid=0,
        qid=que.qid,
        uid=user.uid,
        text=answer.text,
    )
    await db.execute(table.insert(obj.dict()))
    return {'msg': 'Answer create successfully'}


@app.get("/answer/info", tags=['answer'])
async def answer_info(
        answer: AnswerInDB = Depends(get_answer),
        user: Optional[UserInDB] = Depends(login_user_possible),
) -> Answer:
    async def count_vote(stat: str) -> int:
        return await db.fetch_val(
            vote.table.count(
                and_(
                    vote.table.c.aid == answer.aid,
                    vote.table.c.status == stat,
                )))

    async def full_comment(obj: Mapping) -> Comment:
        com = CommentInDB.parse_obj(obj)
        user = await get_full_user(com.uid)
        return Comment.parse_obj({**com.dict(), 'user': user.dict()})

    ans_user = await get_full_user(answer.uid)
    comments = [
        await full_comment(com) for com in await db.fetch_all(
            comment.table.select(comment.table.c.aid == answer.aid))
    ]
    return Answer.parse_obj({
        **answer.dict(),
        'user':
        ans_user.dict(),
        'voteup_cnt':
        await count_vote(vote.VoteStatus.up),
        'votedown_cnt':
        await count_vote(vote.VoteStatus.down),
        'vote_status':
        'neither',
        'comment':
        comments,
    })


@app.post("/answer/modify", tags=['answer'])
async def modify_answer(
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


@app.get("/answer/vote", tags=['vote'])
async def answer_vote(
        stat: vote.VoteStatus,
        answer: AnswerInDB = Depends(get_answer),
        user: UserInDB = Depends(login_user),
):
    if answer.uid == user.uid:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="can't vote yourself",
        )
    obj = await db.fetch_one(
        vote.table.select(
            and_(
                vote.table.c.aid == answer.aid,
                vote.table.c.uid == user.uid,
            )))
    if obj:
        cur = obj['status']
    else:
        cur = vote.VoteStatus.neither

    if cur == stat:
        return {'msg': f'already vote: {cur}'}
    else:
        if stat == vote.VoteStatus.neither:
            await db.execute(
                vote.table.delete(
                    and_(
                        vote.table.c.aid == answer.aid,
                        vote.table.c.uid == user.uid,
                    )))
        elif obj:
            await db.execute(
                vote.table.update(
                    and_(
                        vote.table.c.aid == answer.aid,
                        vote.table.c.uid == user.uid,
                    ),
                    {'status': stat},
                ))
        else:
            await db.execute(
                vote.table.insert(
                    vote.Vote(
                        aid=answer.aid,
                        uid=user.uid,
                        status=stat,
                    ).dict()))
        return {'msg': f'current vote status: {stat}'}


@app.post("/answer/comment", tags=['answer'])
async def leave_comment(
        com: CommentCreate,
        answer: AnswerInDB = Depends(get_answer),
        user: UserInDB = Depends(login_user),
):
    await db.execute(
        comment.table.insert(
            CommentInDB(
                cid=0,
                aid=answer.aid,
                uid=user.uid,
                text=com.text,
            ).dict()))
    return {'msg': 'Comment create successfully'}
