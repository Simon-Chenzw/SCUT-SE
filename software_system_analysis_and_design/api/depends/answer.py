from typing import Optional

from fastapi import HTTPException, status

from ..data import db
from ..depends.question import get_question
from ..depends.user import get_full_user
from ..depends.vote import vote_count, vote_stat
from ..typing import vote
from ..typing.answer import Answer, AnswerInDB, table
from ..typing.user import UserInDB


async def get_answer(aid: int) -> AnswerInDB:
    obj = await db.fetch_one(table.select(table.c.aid == aid))
    if not obj:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"aid {aid} does not exist",
        )
    return AnswerInDB.parse_obj(obj)


async def get_full_answer(
    answer: AnswerInDB,
    user: Optional[UserInDB],
) -> Answer:
    vote_up, vote_down = await vote_count(answer.aid)
    ans_user = await get_full_user(answer.uid)
    que = await get_question(answer.qid)

    if user:
        cur_stat = await vote_stat(answer.aid, user.uid)
    else:
        cur_stat = vote.VoteStatus.neither

    return Answer.parse_obj({
        **answer.dict(),
        'user': ans_user.dict(),
        'question': que.dict(),
        'voteup_cnt': vote_up,
        'votedown_cnt': vote_down,
        'vote_status': cur_stat,
    })
