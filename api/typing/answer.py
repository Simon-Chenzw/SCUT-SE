from pydantic import BaseModel  # pylint: disable=no-name-in-module
from typing import Optional
from enum import Enum
from .user import User


class VoteStatus(str, Enum):
    up = 'up'
    down = 'down'
    neither = 'neither'


class Answer(BaseModel):
    aid: int
    qid: int
    user: User
    text: str
    # comment:
    voteup_cnt: int
    votedown_cnt: int
    vote_status: VoteStatus
    create_time: int
    edited_time: Optional[int]
