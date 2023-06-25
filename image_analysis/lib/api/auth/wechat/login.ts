import { ResponseBase } from "@/lib/api"

export interface WechatLoginRequest {
  code: string
  state?: string
}

export type WechatLoginResponse = ResponseBase

export async function wechatLoginRequest(
  payload: WechatLoginRequest
): Promise<WechatLoginResponse> {
  const resp = await fetch("/api/auth/wechat/login", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload),
  })

  return await resp.json()
}
