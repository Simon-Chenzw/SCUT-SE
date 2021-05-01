import sqlalchemy
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..data import meta
from .user import User

table = sqlalchemy.Table(
    'comment',
    meta,
    sqlalchemy.Column(
        'cid',
        sqlalchemy.INTEGER,
        primary_key=True,
        autoincrement=True,
        nullable=False,
    ),
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
        'text',
        sqlalchemy.TEXT,
        nullable=False,
    ),
)


class CommentInDB(BaseModel):
    cid: int
    aid: int
    uid: int
    text: str


class Comment(CommentInDB):
    user: User


class CommentCreate(BaseModel):
    text: str
