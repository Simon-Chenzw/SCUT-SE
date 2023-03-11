import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { RegisterRequest, RegisterResponse } from "@/lib/api/register"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import argon2 from "argon2"
import { setCookie } from "cookies-next"

export default async function handler(
  req: JsonApiRequest<RegisterRequest>,
  res: JsonApiResponse<RegisterResponse>
) {
  if (req.method !== "POST") {
    return res
      .status(405)
      .send({ code: 405, message: "Only POST requests allowed" })
  }

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

    setCookie("jwt", new Token(user.id).to_jwt(), {
      req,
      res,
      maxAge: 2 * Token.EXP,
      httpOnly: true,
      sameSite: "strict",
      // secure: true, // HTTPS-Only
    })

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
