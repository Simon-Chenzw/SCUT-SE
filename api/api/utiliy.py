from typing import List, Mapping, Any

from ..app import app
from ..data import db
from ..typing.user import table


@app.get("/user/all", response_model=List[Mapping[str, Any]], tags=['debug'])
async def all_users() -> List[Mapping[str, Any]]:
    return await db.fetch_all(table.select().with_only_columns(
        [table.c.uid, table.c.name]))
