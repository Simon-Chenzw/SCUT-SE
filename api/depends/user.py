from typing import Optional

from fastapi import Cookie, Depends, HTTPException, status
from fastapi.security import OAuth2PasswordBearer

from ..data import db
from ..typing import answer, follow, vote
from ..typing.crypto import jwtToken
from ..typing.user import User, UserInDB, table

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token", auto_error=False)


async def get_user(uid: int) -> UserInDB:
    obj = await db.fetch_one(table.select(table.c.uid == uid))
    if obj is None:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail=f"uid {uid} not found",
        )
    return UserInDB.parse_obj(obj)


async def get_full_from_InDB(user: UserInDB) -> User:
    follower = await db.fetch_val(
        follow.table.count(follow.table.c.followed == user.uid))
    voteup = await db.fetch_val(
        vote.table.join(
            answer.table,
            vote.table.c.aid == answer.table.c.aid,
        ).count(answer.table.c.uid == user.uid))
    return User.parse_obj({
        **user.dict(),
        'follower': follower,
        'voteup': voteup,
    })


async def get_full_user(uid: int) -> User:
    return await get_full_from_InDB(await get_user(uid))


async def getToken(
        header_token: Optional[str] = Depends(oauth2_scheme),
        token: Optional[str] = Cookie(None),
) -> str:
    ret = header_token or token
    if ret:
        return ret
    else:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Could not find token",
            headers={"WWW-Authenticate": "Bearer"},
        )


async def login_user(token: str = Depends(getToken)) -> UserInDB:
    try:
        uid = jwtToken.decode(token).sub
        obj = await db.fetch_one(table.select(table.c.uid == uid))
        assert obj
        return UserInDB.parse_obj(obj)
    except:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Could not validate credentials, please login",
            headers={"WWW-Authenticate": "Bearer"},
        )


async def login_user_possible(token: str = Depends(
    getToken)) -> Optional[UserInDB]:
    try:
        return await login_user(token)
    except:
        pass
