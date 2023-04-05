import { ResponseBase } from "@/lib/api"
import { RequestObject } from "@/lib/api/request"

export interface RequestGetResponse extends ResponseBase {
  data?: RequestObject
}

export async function requestGetRequest(
  rid: RequestObject["id"]
): Promise<RequestGetResponse> {
  const resp = await fetch(`/api/request/${rid}`)
  return await resp.json()
}
