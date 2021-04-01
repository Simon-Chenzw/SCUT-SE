from fastapi import FastAPI

app = FastAPI(title='uml homework', )


@app.get('/')
async def root():
    return {'msg': 'hello world'}
