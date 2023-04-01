import { ResponseBase } from "@/lib/api"
import { RequestObject } from "@/lib/api/request"

export interface RequestGetRequest {
  id: RequestObject["id"]
}

export interface RequestGetResponse extends ResponseBase {
  data?: RequestObject
}

export async function requestGetRequest(
  payload: RequestGetRequest
): Promise<RequestGetResponse> {
  const resp = await fetch(`/api/request/${payload.id}`, {
    method: "GET",
    headers: { "Content-Type": "application/json" },
  })

  return await resp.json()
}
