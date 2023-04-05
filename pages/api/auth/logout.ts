import { JsonApiResponse } from "@/lib/api"
import { LogoutResponse } from "@/lib/api/auth/logout"
import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import Token from "@/lib/auth"
import { NextApiRequest } from "next"

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<LogoutResponse>
) {
  if (!isMethodRequestOrSetResponse(req, res, "GET")) return

  Token.delete_cookie(req, res)

  return res.status(200).json({ code: 0, message: "ok" })
}
