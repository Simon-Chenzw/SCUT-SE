from enum import Enum

import sqlalchemy
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..data import meta

table = sqlalchemy.Table(
    'vote',
    meta,
    sqlalchemy.Column(
        'aid',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('answer.aid'),
        nullable=False,
    ),
    sqlalchemy.Column(
        'uid',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('user.uid'),
        nullable=False,
    ),
    sqlalchemy.Column(
        'status',
        sqlalchemy.TEXT,
        nullable=False,
        default='neither',
    ),
)


class VoteStatus(str, Enum):
    up = 'up'
    down = 'down'
    neither = 'neither'


class Vote(BaseModel):
    aid: int
    uid: int
    status: VoteStatus
