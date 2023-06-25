import { ResponseBase } from "@/lib/api"
import { Prisma } from "@/lib/prisma-client"

export type MeInfo = Prisma.UserGetPayload<object>

export interface MeResponse extends ResponseBase {
  data?: MeInfo
}

export async function meRequest(): Promise<MeResponse> {
  const resp = await fetch("/api/auth/me")
  return await resp.json()
}
