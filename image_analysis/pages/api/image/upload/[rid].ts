import { JsonApiResponse } from "@/lib/api"
import {
  isContentTypeOrSetResponse,
  isMethodRequestOrSetResponse,
} from "@/lib/api/helper"
import { getRequestOrSetResponse } from "@/lib/api/helper/request"
import { ImageUploadResponse } from "@/lib/api/image/upload"
import prisma from "@/lib/prisma"
import { IncomingMessage } from "http"
import { NextApiRequest, PageConfig } from "next"

export const config: PageConfig = {
  api: {
    bodyParser: false,
  },
}

async function getFormData(request: IncomingMessage): Promise<FormData> {
  const headers: [string, string][] = []
  for (const k in request.headers) {
    const v = request.headers[k]
    if (v === undefined) continue
    else if (!Array.isArray(v)) headers.push([k, v])
    else for (const vv of v) headers.push([k, vv])
  }

  const buffer: Buffer[] = []
  for await (const chunk of request as AsyncIterable<Buffer>) buffer.push(chunk)

  const response = new Response(Buffer.concat(buffer), { headers: headers })
  return await response.formData()
}

export default async function handler(
  req: NextApiRequest,
  res: JsonApiResponse<ImageUploadResponse>
) {
  if (!isMethodRequestOrSetResponse(req, res, "POST")) return
  if (!isContentTypeOrSetResponse(req, res, "multipart/form-data")) return

  const request = await getRequestOrSetResponse(
    req,
    res,
    req.query.rid as string
  )
  if (request === null) return

  if (request.image !== null)
    return res.status(400).json({
      code: -1,
      message: "The request already contains an image",
    })

  const form = await getFormData(req)
  const image = form.get("image")
  if (image === null)
    return res.status(400).json({
      code: -1,
      message: "Failed to parse the image",
    })
  else if (typeof image === "string" || image instanceof String)
    return res.status(400).json({
      code: -1,
      message: "The payload is not a file",
    })

  try {
    await prisma.image.create({
      data: {
        mimeType: image.type,
        blob: Buffer.from(await image.arrayBuffer()),
        requestId: req.query.rid as string,
      },
    })
  } catch (e) {
    console.log(e)

    return res.status(400).json({
      code: -1,
      message: "Failed to upload the image",
    })
  }

  res.status(200).json({ code: 0, message: "OK" })
}
