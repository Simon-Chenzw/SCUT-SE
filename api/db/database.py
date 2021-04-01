from databases import Database
from sqlalchemy import MetaData, create_engine

from ..app import app
from ..env import dburl_dbs, dburl_sqlalchemy

db = Database(dburl_dbs)

engine = create_engine(
    dburl_sqlalchemy,
    echo=True,
)
meta = MetaData(bind=engine)


@app.on_event("startup")
async def startup():
    await db.connect()


@app.on_event("shutdown")
async def shutdown():
    await db.disconnect()


@app.get('/db/create')
async def db_create():
    meta.create_all()
