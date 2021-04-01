import importlib
import pkgutil

path = __path__
prefix = __name__
modules = {}

if prefix[-1] != '.':
    prefix += '.'
for moduleInfo in pkgutil.iter_modules(path, prefix):
    name = moduleInfo.name
    modules[name] = importlib.import_module(name)
