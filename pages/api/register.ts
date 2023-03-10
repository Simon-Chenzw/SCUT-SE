import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import { RegisterRequest, RegisterResponse } from "@/lib/api/register"

export default async function handler(
  req: JsonApiRequest<RegisterRequest>,
  res: JsonApiResponse<RegisterResponse>
) {
  if (req.method !== "POST") {
    res.status(405).send({ code: 405, message: "Only POST requests allowed" })
    return
  }

  // TODO

  res.status(200).json({ code: 0, message: "ok" })
}
