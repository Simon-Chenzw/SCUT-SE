import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { isJsonRequestOrSetResponse } from "@/lib/api/helper"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import { RequestListRequest, RequestListResponse } from "@/lib/api/request/list"
import prisma from "@/lib/prisma"

export default async function handler(
  req: JsonApiRequest<RequestListRequest>,
  res: JsonApiResponse<RequestListResponse>
) {
  if (!isJsonRequestOrSetResponse(req, res)) return

  const token = getTokenOrSetResponse(req, res)
  if (token === null) return

  return res.status(200).json({
    code: 0,
    message: "ok",
    data: {
      count: await prisma.request.count({ where: { userId: token.id } }),
      requests: await prisma.request.findMany({
        // pagination
        take: req.body.limit,
        skip: req.body.searchAfter ? 1 : 0,
        ...(req.body.searchAfter && { cursor: { id: req.body.searchAfter } }),

        where: { userId: token.id },
        include: { image: { select: { id: true } }, machinedResult: true },
        orderBy: [{ createdAt: "desc" }, { id: "desc" }],
      }),
    },
  })
}
