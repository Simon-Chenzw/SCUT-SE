import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { LogoutResponse } from "@/lib/api/logout"
import Token from "@/lib/auth"
import { deleteCookie } from "cookies-next"

export default async function handler(
  req: JsonApiRequest,
  res: JsonApiResponse<LogoutResponse>
) {
  if (req.method !== "GET") {
    return res
      .status(405)
      .send({ code: 405, message: "Only GET requests allowed" })
  }

  deleteCookie("jwt", {
    req,
    res,
    maxAge: 2 * Token.EXP,
    httpOnly: true,
    sameSite: "strict",
    // secure: true, // HTTPS-Only
  })

  return res.status(200).json({ code: 0, message: "ok" })
}
