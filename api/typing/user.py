from enum import Enum
from typing import Optional
import sqlalchemy
from ..data import meta
from pydantic import BaseModel, EmailStr  # pylint: disable=no-name-in-module

table = sqlalchemy.Table(
    'users',
    meta,
    sqlalchemy.Column(
        'uid',
        sqlalchemy.Integer,
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
        'mail',
        sqlalchemy.TEXT,
    ),
    sqlalchemy.Column(
        'gender',
        sqlalchemy.VARCHAR(10),
        default='not_given',
    ),
)


class Gender(str, Enum):
    male = 'male'
    female = 'female'
    other = 'other'
    not_given = 'not_given'


class User(BaseModel):
    uid: int
    name: str
    mail: Optional[EmailStr]
    gender: Gender = Gender.not_given


class UserInDB(User):
    hash_pwd: str


class UserCreate(UserInDB):
    uid: None = None
