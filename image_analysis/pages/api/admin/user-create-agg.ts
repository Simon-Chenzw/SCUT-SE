import { JsonApiResponse } from "@/lib/api"
import { UserCreateAgg } from "@/lib/api/admin/user-create-agg"
import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import prisma from "@/lib/prisma"
import { NextApiRequest } from "next"

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<UserCreateAgg>
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
    data: (
      await prisma.user.findMany({
        select: { createdAt: true },
      })
    ).map((v) => v.createdAt),
  })
}
