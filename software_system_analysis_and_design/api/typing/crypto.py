from __future__ import annotations

from datetime import datetime, timedelta
from typing import Optional

from jose import jwt
from pydantic import BaseModel  # pylint: disable=no-name-in-module

from ..env import SECRET_KEY
from .user import UserInDB


class Token(BaseModel):
    access_token: str
    token_type: str


class jwtToken(BaseModel):
    # username
    sub: str
    # Expiration
    exp: datetime
    # Issuance time
    iat: datetime

    def encode(self) -> str:
        return jwt.encode(
            self.dict(),
            SECRET_KEY,
            algorithm="HS256",
        )

    @classmethod
    def gen_newjwt(cls, user: UserInDB) -> str:
        utcnow = datetime.utcnow()
        obj = cls(
            sub=user.uid,
            iat=utcnow,
            exp=utcnow + timedelta(minutes=30),
        )
        return obj.encode()

    @staticmethod
    def decode(token: Optional[str]) -> Optional[jwtToken]:
        if not token:
            return None
        return jwtToken.parse_obj(
            jwt.decode(
                token,
                SECRET_KEY,
                algorithms=["HS256"],
            ))
