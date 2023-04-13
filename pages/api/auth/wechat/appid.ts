import { WECHAT_APP_ID } from "@/lib/wechat"
import { NextApiRequest, NextApiResponse } from "next"

export default async function handler(
  req: NextApiRequest,
  res: NextApiResponse
) {
  res.status(200).setHeader("content-type", "text/plain").send(WECHAT_APP_ID)
}
