import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import { NextApiRequest, NextApiResponse } from "next"

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  if (isMethodRequestOrSetResponse(req, res, "GET")) return

  const iid = req.query.iid as string

  const token = Token.from_cookie(req, res)
  if (token === null)
    return res.status(401).send({ code: -1, message: "Unauthorized" })

  const image = await prisma.image.findUnique({
    where: { id: iid },
    include: { request: true },
  })
  if (image === null)
    return res.status(400).send({
      code: -1,
      message: "Image does not exist",
    })
  else if (image.request.userId !== token.id)
    return res.status(400).send({
      code: -1,
      message: "Not authorized to get the image",
    })

  res.setHeader("Content-Type", image.mimeType)
  res.send(image.blob)
}
