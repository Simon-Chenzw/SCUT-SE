from typing import Optional

from fastapi import Depends, HTTPException, Response, status
from fastapi.security import OAuth2PasswordRequestForm
from passlib.context import CryptContext
from sqlalchemy import and_

from ..app import app
from ..data import db
from ..depends.user import (get_full_from_InDB, get_full_user, get_user,
                            login_user, login_user_possible)
from ..typing import follow
from ..typing.crypto import Token, jwtToken
from ..typing.user import User, UserCreate, UserInDB, UserModify, table

pwd_context = CryptContext(schemes=["bcrypt"], deprecated="auto")


async def authenticate(name: str, pwd: str, response: Response) -> Token:
    try:
        obj = await db.fetch_one(table.select(table.c.name == name))
        assert obj
        user = UserInDB.parse_obj(obj)
        assert pwd_context.verify(pwd, user.hash_pwd)
    except:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Incorrect username or password",
            headers={"WWW-Authenticate": "Bearer"},
        )
    else:
        token = jwtToken.gen_newjwt(user)
        response.set_cookie('token', token)
        return Token(access_token=token, token_type="bearer")


@app.post("/user/create", response_model=Token, tags=['authentication'])
async def user_create(
    user: UserCreate,
    response: Response,
) -> Token:
    if len(user.username) > 30:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="username too long",
        )
    if await db.fetch_val(table.count(table.c.name == user.username)):
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="username repeat",
        )
    obj = UserInDB(
        uid=0,
        name=user.username,
        hash_pwd=pwd_context.hash(user.password),
    )
    await db.execute(table.insert(obj.dict()))
    return await authenticate(user.username, user.password, response)


@app.get("/user/info", response_model=User, tags=['user'])
async def user_info(
        uid: int = 0,
        current_user: Optional[UserInDB] = Depends(login_user_possible),
) -> User:
    if uid:
        return await get_full_user(uid)
    elif current_user:
        return await get_full_from_InDB(current_user)
    else:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="need to login",
            headers={"WWW-Authenticate": "Bearer"},
        )


@app.post("/user/modify", tags=['user'])
async def user_modify(
        mod: UserModify,
        user: UserInDB = Depends(login_user),
):
    if mod.name != user.name:
        if await db.fetch_val(table.count(table.c.name == mod.name)):
            raise HTTPException(
                status_code=status.HTTP_400_BAD_REQUEST,
                detail=f"name {mod.name} already used",
            )
    for k in mod.dict():
        if getattr(mod, k) is None:
            setattr(mod, k, getattr(user, k))
    await db.execute(table.update(
        table.c.uid == user.uid,
        mod.dict(),
    ))
    return {'msg': 'User info modify successfully'}


@app.get("/user/login", response_model=Token, tags=['authentication'])
async def login(username: str, password: str, response: Response) -> Token:
    return await authenticate(username, password, response)


@app.get("/user/logout", tags=['authentication'])
async def logout(response: Response):
    response.set_cookie('token', '', expires=1)
    return {'msg': 'logout success'}


@app.post("/token", response_model=Token, tags=['authentication'])
async def login_form(
        response: Response,
        form_data: OAuth2PasswordRequestForm = Depends(),
) -> Token:
    return await authenticate(form_data.username, form_data.password, response)


@app.get("/user/all", tags=['user'])
async def all_users():
    return await db.fetch_all(table.select().with_only_columns(
        [table.c.uid, table.c.name]))


@app.get("/user/follow", tags=['user'])
async def user_follow(
        followed: UserInDB = Depends(get_user),
        user: UserInDB = Depends(login_user),
):
    if followed.uid == user:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="you can't follow yourself",
        )

    if await db.fetch_val(
            follow.table.count(
                and_(
                    follow.table.c.following == user.uid,
                    follow.table.c.followed == followed.uid,
                ))):
        return {'msg': 'Already followed'}

    await db.execute(
        follow.table.insert({
            'following': user.uid,
            'followed': followed.uid,
        }))
    return {'msg': 'Successfully follow'}


@app.get("/user/unfollow", tags=['user'])
async def user_unfollow(
        followed: UserInDB = Depends(get_user),
        user: UserInDB = Depends(login_user),
):
    if followed.uid == user:
        raise HTTPException(
            status_code=status.HTTP_400_BAD_REQUEST,
            detail="you can't unfollow yourself",
        )

    if await db.fetch_val(
            follow.table.count(
                and_(
                    follow.table.c.following == user.uid,
                    follow.table.c.followed == followed.uid,
                ))) == 0:
        return {'msg': 'Originally unfollow'}

    await db.execute(
        follow.table.delete(
            and_(
                follow.table.c.following == user.uid,
                follow.table.c.followed == followed.uid,
            )))
    return {'msg': 'Successfully unfollow'}
