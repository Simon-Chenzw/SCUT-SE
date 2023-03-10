import { ResponseBase } from "@/lib/api"

export interface RegisterRequest {
  name: string
  email: string
  password: string
  password_repeat: string
}

export type RegisterResponse = ResponseBase

export async function registerRequest(
  payload: RegisterRequest
): Promise<RegisterResponse> {
  const resp = await fetch("/api/register", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload),
  })

  return await resp.json()
}
