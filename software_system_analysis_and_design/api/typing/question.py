import sqlalchemy
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..data import meta

table = sqlalchemy.Table(
    'question',
    meta,
    sqlalchemy.Column(
        'qid',
        sqlalchemy.INTEGER,
        primary_key=True,
        autoincrement=True,
        nullable=False,
    ),
    sqlalchemy.Column(
        'title',
        sqlalchemy.VARCHAR(100),
        unique=True,
        nullable=False,
    ),
    sqlalchemy.Column(
        'desc',
        sqlalchemy.TEXT,
        nullable=False,
    ),
)


class Question(BaseModel):
    qid: int
    title: str
    desc: str


class QuestionCreate(BaseModel):
    title: str
    desc: str
