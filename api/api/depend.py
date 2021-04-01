from typing import Optional

from fastapi import Depends, HTTPException, status, Cookie
from fastapi.security import OAuth2PasswordBearer
from ..typing.user import UserInDB
from ..typing.crypto import jwtToken
from ..db.user import db_user_query_username

oauth2_scheme = OAuth2PasswordBearer(tokenUrl="token", auto_error=False)


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


async def get_user(token: str = Depends(getToken)) -> UserInDB:
    credentials_exception = HTTPException(
        status_code=status.HTTP_401_UNAUTHORIZED,
        detail="Could not validate credentials",
        headers={"WWW-Authenticate": "Bearer"},
    )
    name = jwtToken.decode(token).sub
    if not name:
        raise credentials_exception
    user = await db_user_query_username(name)
    if user is None:
        raise credentials_exception
    return user


async def possible_user(token: str = Depends(getToken)) -> Optional[UserInDB]:
    try:
        return await get_user(token)
    except:
        pass