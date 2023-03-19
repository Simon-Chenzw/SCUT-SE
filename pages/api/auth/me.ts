import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { MeResponse } from "@/lib/api/auth/me"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"

export default async function handler(
  req: JsonApiRequest,
  res: JsonApiResponse<MeResponse>
) {
  if (req.method !== "GET") {
    return res
      .status(405)
      .send({ code: 405, message: "Only GET requests allowed" })
  }

  const token = Token.from_cookie(req, res)
  if (token !== null) {
    const user = await prisma.user.findUnique({
      where: { id: token.id },
    })
    if (user !== null) {
      return res.status(200).json({
        code: 0,
        message: "ok",
        data: {
          id: user.id,
          name: user.name,
          email: user.email,
        },
      })
    } else {
      return res.status(401).json({
        code: -1,
        message: "user not exists",
      })
    }
  } else {
    return res.status(401).json({
      code: -1,
      message: "get info from jwt failed",
    })
  }
}
