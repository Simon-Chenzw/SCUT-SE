import { isMethodRequestOrSetResponse } from "@/lib/api/helper"
import { getTokenOrSetResponse } from "@/lib/api/helper/token"
import prisma from "@/lib/prisma"
import { NextApiRequest, NextApiResponse } from "next"

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  if (!isMethodRequestOrSetResponse(req, res, "GET")) return

  const iid = req.query.iid as string

  const token = getTokenOrSetResponse(req, res)
  if (token === null) return

  const image = await prisma.image.findUnique({
    where: { id: iid },
    select: { updatedAt: true, request: { select: { userId: true } } },
  })
  if (image === null)
    return res.status(400).json({
      code: -1,
      message: "Image does not exist",
    })
  else if (image.request.userId !== token.id)
    return res.status(400).json({
      code: -1,
      message: "Not authorized to get the image",
    })

  // Check if modified, Save database resources
  const ifModifiedSince = req.headers["if-modified-since"]
  if (
    ifModifiedSince !== undefined &&
    new Date(ifModifiedSince) >= new Date(image.updatedAt.toUTCString())
  )
    return res.status(304).end()

  // respond
  const image_content = await prisma.image.findUnique({
    where: { id: iid },
    select: { mimeType: true, blob: true, updatedAt: true },
  })

  if (image_content) {
    res.setHeader("Content-Type", image_content.mimeType)
    res.setHeader("Last-Modified", image_content.updatedAt.toUTCString())
    res.setHeader("Cache-Control", "private, max-age=7200")
    res.send(image_content.blob)
  } else {
    res.end()
  }
}
