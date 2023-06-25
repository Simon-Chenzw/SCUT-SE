import { ResponseBase } from "@/lib/api"
import { RequestObject } from "@/lib/api/request"

export interface RequestListRequest {
  searchAfter?: RequestObject["id"]
  limit?: number
}

export interface RequestListResponse extends ResponseBase {
  data?: {
    count: number
    requests: RequestObject[]
  }
}

export async function requestListRequest(
  payload: RequestListRequest
): Promise<RequestListResponse> {
  const resp = await fetch("/api/request/list", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify(payload),
  })

  return await resp.json()
}
