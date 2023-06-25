import sqlalchemy
from ..data import meta
from typing import Optional
from pydantic import BaseModel, HttpUrl  # pylint: disable=no-name-in-module

table = sqlalchemy.Table(
    'user',
    meta,
    sqlalchemy.Column(
        'uid',
        sqlalchemy.INTEGER,
        primary_key=True,
        autoincrement=True,
        nullable=False,
    ),
    sqlalchemy.Column(
        'name',
        sqlalchemy.VARCHAR(30),
        unique=True,
        nullable=False,
    ),
    sqlalchemy.Column(
        'hash_pwd',
        sqlalchemy.CHAR(60),
        nullable=False,
    ),
    sqlalchemy.Column(
        'avatar',
        sqlalchemy.TEXT,
        nullable=True,
    ),
    sqlalchemy.Column(
        'introduction',
        sqlalchemy.TEXT,
        nullable=True,
    ),
)


class UserBase(BaseModel):
    uid: int
    name: str
    avatar: Optional[HttpUrl]
    introduction: Optional[str]


class UserInDB(UserBase):
    hash_pwd: str


class User(UserBase):
    follower: int
    voteup: int


class UserCreate(BaseModel):
    username: str
    password: str


class UserModify(BaseModel):
    name: Optional[str]
    avatar: Optional[HttpUrl]
    introduction: Optional[str]
