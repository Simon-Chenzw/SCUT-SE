from pydantic import BaseModel, EmailStr  # pylint: disable=no-name-in-module
from typing import Optional
from enum import Enum


class Gender(str, Enum):
    male = 'male'
    female = 'female'
    other = 'other'
    not_given = 'not_given'


class User(BaseModel):
    uid: int
    name: str
    mail: EmailStr
    gender: Gender


class VoteStatus(BaseModel):
    pass


class Question(BaseModel):
    qid: int
    title: str
    desc: str


class Answer(BaseModel):
    aid: int
    qid: int
    user: User
    text: str
    # comment:
    vote: VoteStatus
    create_time: int
    edited_time: Optional[int]
