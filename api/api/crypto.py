from fastapi import Depends, HTTPException, Response, status
from fastapi.security import OAuth2PasswordRequestForm

from ..db.user import authenticate_user, db_user_insert, pwd_context, db_user_query_uid
from ..typing.crypto import Token, jwtToken
from ..typing.user import User, UserInDB
from ..app import app
from .depend import get_user, possible_user


async def authenticate(name: str, pwd: str, response: Response):
    user = await authenticate_user(name, pwd)
    if not user:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="Incorrect username or password",
            headers={"WWW-Authenticate": "Bearer"},
        )
    access_token = jwtToken.gen_newjwt(user)
    response.set_cookie('token', access_token)
    return {"access_token": access_token, "token_type": "bearer"}


@app.get("/user/register", response_model=Token, tags=['authentication'])
async def create_user(username: str, password: str, response: Response):
    obj = UserInDB(
        mail='someone@example.com',
        name=username,
        hash_pwd=pwd_context.hash(password),
    )
    await db_user_insert(obj)
    return await authenticate(username, password, response)


@app.get("/user/info", response_model=User, tags=['user'])
async def read_users_me(
        uid: int = 0,
        current_user: User = Depends(possible_user),
):
    if uid:
        return await db_user_query_uid(uid)
    elif current_user:
        return current_user
    else:
        raise HTTPException(
            status_code=status.HTTP_401_UNAUTHORIZED,
            detail="need to login",
            headers={"WWW-Authenticate": "Bearer"},
        )


@app.get("/user/login", response_model=Token, tags=['authentication'])
async def login(username: str, password: str, response: Response):
    return await authenticate(username, password, response)


@app.get("/user/logout", tags=['authentication'])
async def logout(response: Response):
    response.set_cookie('token', '', expires=1)
    return {'msg': 'logout success'}


@app.post("/token", response_model=Token, tags=['authentication'])
async def login_for_access_token(
        response: Response,
        form_data: OAuth2PasswordRequestForm = Depends(),
):
    return await authenticate(form_data.username, form_data.password, response)


@app.get("/user/all")
async def get_all_users():
    from ..db.database import db
    return await db.fetch_all("select name from users;")
