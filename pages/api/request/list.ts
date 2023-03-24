import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { RequestListRequest, RequestListResponse } from "@/lib/api/request/list"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"

export default async function handler(
  req: JsonApiRequest<RequestListRequest>,
  res: JsonApiResponse<RequestListResponse>
) {
  if (req.method !== "POST") {
    return res
      .status(405)
      .send({ code: 405, message: "Only POST requests allowed" })
  }

  const token = Token.from_cookie(req, res)
  if (token === null) {
    return res.status(401).json({
      code: -1,
      message: "please login",
    })
  }

  return res.status(200).json({
    code: 0,
    message: "ok",
    data: {
      count: await prisma.request.count({
        where: {
          userId: token.id,
        },
      }),
      requests: await prisma.request.findMany({
        take: req.body.pagination?.limit,
        skip: req.body.pagination?.offset,
        where: {
          userId: token.id,
        },
        include: {
          image: true,
          machinedResult: true,
        },
        orderBy: {
          createdAt: "desc",
        },
      }),
    },
  })
}
