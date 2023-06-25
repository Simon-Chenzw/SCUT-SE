import importlib
import pkgutil
from os import path

from fastapi import FastAPI

app = FastAPI(title='uml homework', )


@app.get('/')
async def root():
    return {'msg': 'hello world'}


modules = {}

for name in ['api', 'typing']:
    for moduleInfo in pkgutil.iter_modules(
        [path.join(path.split(__file__)[0], name)],
            f'api.{name}.',
    ):
        name = moduleInfo.name
        modules[name] = importlib.import_module(name)
