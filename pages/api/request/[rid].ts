import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { RequestGetRequest, RequestGetResponse } from "@/lib/api/request/[rid]"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"

export default async function handler(
  req: JsonApiRequest<RequestGetRequest>,
  res: JsonApiResponse<RequestGetResponse>
) {
  if (req.method !== "GET") {
    return res
      .status(405)
      .send({ code: 405, message: "Only GET requests allowed" })
  }

  const token = Token.from_cookie(req, res)
  if (token === null) {
    return res.status(401).json({
      code: -1,
      message: "please login",
    })
  }

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
