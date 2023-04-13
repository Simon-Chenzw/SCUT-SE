import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { LoginRequest, LoginResponse } from "@/lib/api/auth/login"
import { isJsonRequestOrSetResponse } from "@/lib/api/helper"
import { setTokenCookie } from "@/lib/api/helper/token"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import argon2 from "argon2"

export default async function handler(
  req: JsonApiRequest<LoginRequest>,
  res: JsonApiResponse<LoginResponse>
) {
  if (!isJsonRequestOrSetResponse(req, res)) return

  const user = await prisma.user.findUnique({
    where: { email: req.body.email },
    include: { credential: true },
  })
  if (user === null)
    return res.status(400).json({ code: -1, message: "user not found" })

  if (user.credential === null)
    return res
      .status(400)
      .json({ code: -1, message: "User has not set a password" })

  if (!(await argon2.verify(user.credential.passwd, req.body.password)))
    return res.status(400).json({ code: -1, message: "password not correct" })
  else {
    setTokenCookie(req, res, new Token(user.id))
    return res.status(200).json({ code: 0, message: "ok" })
  }
}
