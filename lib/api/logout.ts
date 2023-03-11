import { ResponseBase } from "@/lib/api"

export type LogoutResponse = ResponseBase

export async function logoutRequest(): Promise<LogoutResponse> {
  const resp = await fetch("/api/logout", {
    method: "GET",
    headers: { "Content-Type": "application/json" },
  })

  return await resp.json()
}
