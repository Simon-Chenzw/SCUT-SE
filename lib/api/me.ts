import { ResponseBase } from "@/lib/api"

export interface MeResponse extends ResponseBase {
  data?: {
    id: string
    name: string
    email: string
  }
}

export async function meRequest(): Promise<MeResponse> {
  const resp = await fetch("/api/me", {
    method: "GET",
    headers: { "Content-Type": "application/json" },
  })

  return await resp.json()
}
