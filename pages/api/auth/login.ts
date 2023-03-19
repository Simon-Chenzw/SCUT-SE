import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { LoginRequest, LoginResponse } from "@/lib/api/auth/login"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import argon2 from "argon2"

export default async function handler(
  req: JsonApiRequest<LoginRequest>,
  res: JsonApiResponse<LoginResponse>
) {
  if (req.method !== "POST") {
    return res
      .status(405)
      .send({ code: 405, message: "Only POST requests allowed" })
  }

  const user = await prisma.user.findUnique({
    where: { email: req.body.email },
  })

  if (user !== null) {
    if (await argon2.verify(user.passwd, req.body.password)) {
      new Token(user.id).set_cookie(req, res)
      return res.status(200).json({ code: 0, message: "ok" })
    } else {
      return res.status(401).json({ code: -1, message: "password not correct" })
    }
  } else {
    return res.status(401).json({ code: -1, message: "user not found" })
  }
}
