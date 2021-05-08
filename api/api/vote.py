from fastapi import Depends, HTTPException, status
from sqlalchemy import and_

from ..app import app
from ..data import db
from ..depends.answer import get_answer
from ..depends.user import login_user
from ..typing.answer import AnswerInDB
from ..typing.user import UserInDB
from ..typing.vote import Vote, VoteStatus, table


@app.get("/vote/set", tags=['vote'])
async def vote_set(
        stat: VoteStatus,
        answer: AnswerInDB = Depends(get_answer),
        user: UserInDB = Depends(login_user),
):
    if answer.uid == user.uid:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="can't vote yourself",
        )
    obj = await db.fetch_one(
        table.select(and_(
            table.c.aid == answer.aid,
            table.c.uid == user.uid,
        )))
    if obj:
        cur = obj['status']
    else:
        cur = VoteStatus.neither

    if cur == stat:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f'already vote: {cur}',
        )
    else:
        if stat == VoteStatus.neither:
            await db.execute(
                table.delete(
                    and_(
                        table.c.aid == answer.aid,
                        table.c.uid == user.uid,
                    )))
        elif obj:
            await db.execute(
                table.update(
                    and_(
                        table.c.aid == answer.aid,
                        table.c.uid == user.uid,
                    ),
                    {'status': stat},
                ))
        else:
            await db.execute(
                table.insert(
                    Vote(
                        aid=answer.aid,
                        uid=user.uid,
                        status=stat,
                    ).dict()))
        return {'msg': f'current vote status: {stat}'}
