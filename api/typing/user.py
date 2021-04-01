from pydantic import BaseModel, EmailStr  # pylint: disable=no-name-in-module
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
    gender: Gender = Gender.not_given


class UserInDB(User):
    hash_pwd: str
