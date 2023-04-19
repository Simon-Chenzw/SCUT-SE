import { JsonApiResponse } from "@/lib/api"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import { RequestObject } from "@/lib/api/request"
import prisma from "@/lib/prisma"
import { NextApiRequest } from "next"

export async function getRequestOrSetResponse(
  req: NextApiRequest,
  res: JsonApiResponse,
  rid: string
): Promise<RequestObject | null> {
  const token = getTokenOrSetResponse(req, res)
  if (token === null) return null

  const request = await prisma.request.findUnique({
    where: { id: rid },
    include: { image: { select: { id: true } }, machinedResult: true },
  })

  if (request === null) {
    res.status(404).json({
      code: -1,
      message: "Request not found",
    })
    return null
  }

  if (request.userId !== token.id) {
    res.status(401).json({
      code: -1,
      message: "Not authorized to access the request",
    })
    return null
  }

  return request as RequestObject
}
