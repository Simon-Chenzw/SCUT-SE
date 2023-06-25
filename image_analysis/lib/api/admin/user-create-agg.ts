import { ResponseBase } from "@/lib/api"

export interface UserCreateAgg extends ResponseBase {
  data?: Date[]
}

export async function userCreateAggRequest(): Promise<UserCreateAgg> {
  const resp = await fetch("/api/admin/user-create-agg")

  return await resp.json()
}
