from typing import List

import sqlalchemy
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..data import meta
from .user import User
from .question import Question
from .vote import VoteStatus

table = sqlalchemy.Table(
    'answer',
    meta,
    sqlalchemy.Column(
        'aid',
        sqlalchemy.INTEGER,
        primary_key=True,
        autoincrement=True,
        nullable=False,
    ),
    sqlalchemy.Column(
        'qid',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('question.qid'),
        nullable=False,
    ),
    sqlalchemy.Column(
        'uid',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('user.uid'),
        nullable=False,
    ),
    sqlalchemy.Column(
        'text',
        sqlalchemy.TEXT,
        nullable=False,
    ),
)


class AnswerInDB(BaseModel):
    aid: int
    qid: int
    uid: int

    text: str


class Answer(AnswerInDB):
    user: User
    question: Question
    voteup_cnt: int
    votedown_cnt: int
    vote_status: VoteStatus


class AnswerCreate(BaseModel):
    text: str
