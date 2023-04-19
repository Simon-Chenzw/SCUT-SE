import { JsonApiResponse } from "@/lib/api"
import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import { getRequestOrSetResponse } from "@/lib/api/helper/request"
import { RequestObject } from "@/lib/api/request"
import { RequestGetResponse } from "@/lib/api/request/[rid]"
import { NextApiRequest } from "next"

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<RequestGetResponse>
) {
  if (!isMethodRequestOrSetResponse(req, res, "GET")) return

  const request = await getRequestOrSetResponse(
    req,
    res,
    req.query.rid as string
  )
  if (request === null) return

  return res.status(200).json({
    code: 0,
    message: "ok",
    data: request as RequestObject,
  })
}
