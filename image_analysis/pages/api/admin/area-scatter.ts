import { JsonApiResponse } from "@/lib/api"
import {
  AreaScatter,
  AreaScatterResultObject,
} from "@/lib/api/admin/area-scatter"
import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import prisma from "@/lib/prisma"
import { NextApiRequest } from "next"

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<AreaScatter>
) {
  if (!isMethodRequestOrSetResponse(req, res, "GET")) return

  const token = getTokenOrSetResponse(req, res)
  if (token === null) return

  const user = await prisma.user.findUnique({ where: { id: token.id } })
  if (user === null)
    return res.status(401).json({ code: -1, message: "user not exists" })
  if (user.role !== "ADMIN")
    return res.status(401).json({ code: -1, message: "admin" })

  return res.status(200).json({
    code: 0,
    message: "ok",
    data: (await prisma.request.findMany({
      where: {
        machinedResult: { isNot: null },
      },
      select: {
        createdAt: true,
        machinedResult: { select: { data: true } },
      },
    })) as AreaScatterResultObject[],
  })
}
