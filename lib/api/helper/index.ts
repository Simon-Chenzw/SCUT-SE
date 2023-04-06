import { JsonApiResponse } from "@/lib/api"
import { NextApiRequest } from "next"

export type HTTP_METHOD =
  | "GET"
  | "HEAD"
  | "POST"
  | "PUT"
  | "DELETE"
  | "CONNECT"
  | "OPTIONS"
  | "TRACE"
  | "PATCH"

export function isMethodRequestOrSetResponse(
  req: NextApiRequest,
  res: JsonApiResponse,
  method: HTTP_METHOD | HTTP_METHOD[]
): boolean {
  if (
    !Array.isArray(method)
      ? req.method === method
      : req.method !== undefined && (method as string[]).includes(req.method)
  )
    return true

  const allow = Array.isArray(method) ? method.join(", ") : method
  res
    .status(405)
    .setHeader("Allow", allow)
    .json({
      code: -1,
      message: `Only ${allow} requests allowed`,
    })
  return false
}

export function isContentTypeOrSetResponse(
  req: NextApiRequest,
  res: JsonApiResponse,
  contentType: string
): boolean {
  if (!isMethodRequestOrSetResponse(req, res, "POST")) return false

  if (req.headers["content-type"]?.startsWith(contentType)) return true

  res
    .status(415)
    .json({ code: -1, message: `Content-Type must be ${contentType}` })
  if (req.method === "POST") res.setHeader("Accept-Post", contentType)

  return false
}

export function isJsonRequestOrSetResponse(
  req: NextApiRequest,
  res: JsonApiResponse
): boolean {
  if (!isMethodRequestOrSetResponse(req, res, "POST")) return false
  if (!isContentTypeOrSetResponse(req, res, "application/json")) return false
  return true
}
