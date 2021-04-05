from enum import Enum
from typing import Optional

from pydantic import BaseModel, EmailStr  # pylint: disable=no-name-in-module


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
