import { ResponseBase } from "@/lib/api"

export interface MeInfo {
  id: string
  name: string
  email: string
}

export interface MeResponse extends ResponseBase {
  data?: MeInfo
}

export async function meRequest(): Promise<MeResponse> {
  const resp = await fetch("/api/me", {
    method: "GET",
    headers: { "Content-Type": "application/json" },
  })

  return await resp.json()
}
