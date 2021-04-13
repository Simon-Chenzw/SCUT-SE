from typing import Optional

from passlib.context import CryptContext

from ..typing.user import UserInDB, UserCreate, table
from ..data import db

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")


async def db_user_insert(user: UserCreate) -> bool:
    try:
        await db.execute(table.insert(user.dict()))
        return True
    except:
        return False


async def db_user_query_username(name: str) -> Optional[UserInDB]:
    rec = await db.fetch_one(table.select(table.c.name == name))
    if rec:
        return UserInDB.parse_obj(rec)


async def db_user_query_uid(uid: int) -> Optional[UserInDB]:
    rec = await db.fetch_one(table.select(table.c.uid == uid))
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
