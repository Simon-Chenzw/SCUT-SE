import { ResponseBase } from "@/lib/api"

export interface LoginRequest {
  email: string
  password: string
}

export type LoginResponse = ResponseBase

export async function loginRequest(
  payload: LoginRequest
): Promise<LoginResponse> {
  const resp = await fetch("/api/login", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload),
  })

  return await resp.json()
}
