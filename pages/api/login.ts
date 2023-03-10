import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { LoginRequest, LoginResponse } from "@/lib/api/login"

export default async function handler(
  req: JsonApiRequest<LoginRequest>,
  res: JsonApiResponse<LoginResponse>
) {
  if (req.method !== "POST") {
    res.status(405).send({ code: 405, message: "Only POST requests allowed" })
    return
  }

  // TODO

  res.status(200).json({ code: 0, message: "ok" })
}
