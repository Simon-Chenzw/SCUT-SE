import { deleteCookie, getCookie, setCookie } from "cookies-next"
import { OptionsType as CookieOptions } from "cookies-next/lib/types"
import jwt from "jsonwebtoken"
import { NextApiRequest, NextApiResponse } from "next"

const PUBLIC_KEY = process.env.PUBLIC_KEY || ""
const PRIVATE_KEY = process.env.PRIVATE_KEY || ""
const JWT_SIGNING_ALGORITHMS = "RS512"
const JWT_EXPIRES = 30 * 24 * 60 * 60 // 30 days
const JWT_COOKIE_NAME = "jwt"
const JWT_COOKIE_CONFIG: CookieOptions = {
  maxAge: 2 * JWT_EXPIRES,
  httpOnly: true,
  sameSite: "strict",
  // secure: true, // HTTPS-Only
}

export default class Token {
  constructor(public id: string) {}

  to_jwt(): string {
    return jwt.sign({ id: this.id }, PRIVATE_KEY, {
      algorithm: JWT_SIGNING_ALGORITHMS,
      expiresIn: JWT_EXPIRES,
    })
  }

  static from_jwt(token: string): Token | null {
    try {
      const payload = jwt.verify(token, PUBLIC_KEY, {
        algorithms: [JWT_SIGNING_ALGORITHMS],
      })
      if (typeof payload === "string") return null
      else return new Token(payload.id)
    } catch {
      return null
    }
  }

  set_cookie(req: NextApiRequest, res: NextApiResponse): void {
    setCookie(JWT_COOKIE_NAME, this.to_jwt(), {
      req,
      res,
      ...JWT_COOKIE_CONFIG,
    })
  }

  static from_cookie(req: NextApiRequest, res: NextApiResponse): Token | null {
    const jwt = getCookie(JWT_COOKIE_NAME, {
      req,
      res,
      ...JWT_COOKIE_CONFIG,
    })
    if (typeof jwt === "string") {
      return Token.from_jwt(jwt)
    } else {
      return null
    }
  }

  static delete_cookie(req: NextApiRequest, res: NextApiResponse): void {
    deleteCookie(JWT_COOKIE_NAME, {
      req,
      res,
      ...JWT_COOKIE_CONFIG,
    })
  }
}
