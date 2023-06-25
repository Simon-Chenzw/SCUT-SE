import sqlalchemy
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..data import meta

table = sqlalchemy.Table(
    'follow',
    meta,
    sqlalchemy.Column(
        'following',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('user.uid'),
        nullable=False,
    ),
    sqlalchemy.Column(
        'followed',
        sqlalchemy.INTEGER,
        sqlalchemy.ForeignKey('user.uid'),
        nullable=False,
    ),
)


class follow(BaseModel):
    following: int
    followed: int
