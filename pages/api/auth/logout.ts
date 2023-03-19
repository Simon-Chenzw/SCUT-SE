import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { LogoutResponse } from "@/lib/api/auth/logout"
import Token from "@/lib/auth"

export default async function handler(
  req: JsonApiRequest,
  res: JsonApiResponse<LogoutResponse>
) {
  if (req.method !== "GET") {
    return res
      .status(405)
      .send({ code: 405, message: "Only GET requests allowed" })
  }

  Token.delete_cookie(req, res)

  return res.status(200).json({ code: 0, message: "ok" })
}
