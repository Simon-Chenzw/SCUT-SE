import { RequestObject } from "@/lib/api/request"
import { requestGetRequest } from "@/lib/api/request/[rid]"
import { useEffect, useState } from "react"

export function useRequest(
  rid: RequestObject["id"]
): [RequestObject | undefined, () => Promise<void>] {
  const [request, setRequest] = useState<RequestObject>()

  const refreshRequest = async () => {
    const req = await requestGetRequest(rid)
    setRequest(req.data)
  }

  useEffect(() => {
    refreshRequest()
  }, [rid])

  return [request, refreshRequest]
}
