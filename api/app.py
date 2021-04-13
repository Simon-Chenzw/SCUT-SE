import importlib
import pkgutil

from fastapi import FastAPI

app = FastAPI(title='uml homework', )


@app.get('/')
async def root():
    return {'msg': 'hello world'}


path = ['/home/simon/code/uml/api/api']
prefix = 'api.api.'
modules = {}

for moduleInfo in pkgutil.iter_modules(path, prefix):
    name = moduleInfo.name
    modules[name] = importlib.import_module(name)
