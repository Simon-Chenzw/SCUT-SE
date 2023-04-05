import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { RegisterRequest, RegisterResponse } from "@/lib/api/auth/register"
import { isJsonRequestOrSetResponse } from "@/lib/api/helper"
import { setTokenCookie } from "@/lib/api/helper/token"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import argon2 from "argon2"

export default async function handler(
  req: JsonApiRequest<RegisterRequest>,
  res: JsonApiResponse<RegisterResponse>
) {
  if (!isJsonRequestOrSetResponse(req, res)) return

  const { name, email, password } = req.body

  // Note: unchecked

  try {
    const user = await prisma.user.create({
      data: {
        name,
        email,
        passwd: await argon2.hash(password),
      },
    })
    setTokenCookie(req, res, new Token(user.id))
    return res.status(200).json({ code: 0, message: "ok" })
  } catch (e) {
    if (e instanceof Object && "code" in e) {
      if (e.code === "P2002") {
        return res.status(400).json({ code: -1, message: "email existed" })
      }
    }
    throw e
  }
}
