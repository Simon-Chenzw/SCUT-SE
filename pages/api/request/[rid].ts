import { JsonApiResponse } from "@/lib/api"
import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import { RequestGetResponse } from "@/lib/api/request/[rid]"
import prisma from "@/lib/prisma"
import { NextApiRequest } from "next"

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<RequestGetResponse>
) {
  if (!isMethodRequestOrSetResponse(req, res, "GET")) return

  const token = getTokenOrSetResponse(req, res)
  if (token === null) return

  const { rid } = req.query as unknown as { rid: string }

  const request = await prisma.request.findUnique({
    where: { id: rid },
    include: { image: { select: { id: true } }, machinedResult: true },
  })

  if (request === null) {
    return res.status(404).json({
      code: -1,
      message: "not found",
    })
  } else if (request.userId !== token.id) {
    return res.status(401).json({
      code: -1,
      message: "unauthorized",
    })
  } else {
    return res.status(200).json({
      code: 0,
      message: "ok",
      data: request,
    })
  }
}
