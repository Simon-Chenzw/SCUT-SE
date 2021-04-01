from pydantic import BaseModel  # pylint: disable=no-name-in-module


class Question(BaseModel):
    qid: int
    title: str
    desc: str