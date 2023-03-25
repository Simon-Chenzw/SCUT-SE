import { ResponseBase } from "@/lib/api"
import { Prisma } from "@/lib/prisma-client"

export type RequestListObject = Prisma.RequestGetPayload<{
  include: {
    image: true
    machinedResult: true
  }
}>

export interface RequestListRequest {
  searchAfter?: RequestListObject["id"]
  limit?: number
}

export interface RequestListResponse extends ResponseBase {
  data?: {
    count: number
    requests: RequestListObject[]
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
