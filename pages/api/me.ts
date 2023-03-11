import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { MeResponse } from "@/lib/api/me"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import { getCookie } from "cookies-next"

export default async function handler(
  req: JsonApiRequest,
  res: JsonApiResponse<MeResponse>
) {
  if (req.method !== "GET") {
    return res
      .status(405)
      .send({ code: 405, message: "Only GET requests allowed" })
  }

  do {
    const jwt = getCookie("jwt", {
      req,
      res,
      maxAge: 2 * Token.EXP,
      httpOnly: true,
      sameSite: "strict",
      // secure: true, // HTTPS-Only
    })
    if (typeof jwt !== "string") break

    const token = Token.from_jwt(jwt)
    if (token === null) break

    const user = await prisma.user.findUnique({
      where: { id: token.id },
    })
    if (user === null) break

    return res.status(200).json({
      code: 0,
      message: "ok",
      data: {
        id: user.id,
        name: user.name,
        email: user.email,
      },
    })
  } while (
    // eslint-disable-next-line no-constant-condition
    false
  )

  return res.status(401).json({
    code: -1,
    message: "get info from jwt failed",
  })
}
