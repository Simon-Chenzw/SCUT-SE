import { JsonApiResponse } from "@/lib/api"
import Token, { JWT_EXPIRES } from "@/lib/auth"
import { deleteCookie, getCookie, setCookie } from "cookies-next"
import { OptionsType as CookieOptions } from "cookies-next/lib/types"
import { NextApiRequest, NextApiResponse } from "next"

export const JWT_COOKIE_NAME = "jwt"
export const JWT_COOKIE_CONFIG: CookieOptions = {
  maxAge: 2 * JWT_EXPIRES,
  httpOnly: true,
  sameSite: "strict",
  // secure: true, // HTTPS-Only
}

export function getTokenOrSetResponse(
  req: NextApiRequest,
  res: JsonApiResponse
): Token | null {
  const jwt = getCookie(JWT_COOKIE_NAME, {
    req,
    res,
    ...JWT_COOKIE_CONFIG,
  })

  if (typeof jwt === "string") {
    const token = Token.from_jwt(jwt)
    if (token !== null) return token
  }

  res.status(401).json({ code: -1, message: "Unauthorized" })
  return null
}

export function setTokenCookie(
  req: NextApiRequest,
  res: NextApiResponse,
  token: Token
): void {
  setCookie(JWT_COOKIE_NAME, token.to_jwt(), {
    req,
    res,
    ...JWT_COOKIE_CONFIG,
  })
}

export function deleteTokenCookie(req: NextApiRequest, res: NextApiResponse) {
  deleteCookie(JWT_COOKIE_NAME, {
    req,
    res,
    ...JWT_COOKIE_CONFIG,
  })
}
