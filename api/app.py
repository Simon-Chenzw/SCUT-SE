from fastapi import FastAPI
from .typing import User

app = FastAPI(title='uml work', )


@app.get('/')
async def root():
    return {'msg': 'hello world'}


@app.post('/test')
async def test(user: User):
    return user
