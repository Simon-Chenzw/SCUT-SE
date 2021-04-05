from typing import Optional

import sqlalchemy
from passlib.context import CryptContext

from ..typing.user import UserInDB, UserCreate
from .database import db, meta

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")
user_table = sqlalchemy.Table(
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


async def db_user_insert(user: UserCreate) -> bool:
    try:
        await db.execute(user_table.insert(user.dict()))
        return True
    except:
        return False


async def db_user_query_username(name: str) -> Optional[UserInDB]:
    rec = await db.fetch_one(user_table.select(user_table.c.name == name))
    if rec:
        return UserInDB.parse_obj(rec)


async def db_user_query_uid(uid: int) -> Optional[UserInDB]:
    rec = await db.fetch_one(user_table.select(user_table.c.uid == uid))
    if rec:
        return UserInDB.parse_obj(rec)


async def authenticate_user(
    username: str,
    password: str,
) -> Optional[UserInDB]:
    user = await db_user_query_username(username)
    if not user:
        return None
    if not pwd_context.verify(password, user.hash_pwd):
        return None
    return user
