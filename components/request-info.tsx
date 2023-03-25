import { RequestListObject, requestListRequest } from "@/lib/api/request/list"
import { Card, Pagination, Text } from "@mantine/core"
import { useEffect, useState } from "react"

export default function RequestInfo() {
  const [activePage, setPage] = useState(1)
  const [requests, setRequests] = useState<RequestListObject[]>([])

  useEffect(() => {
    const fetchData = async () => {
      for (let i = 1; i <= activePage; i++) {
        const resp = await requestListRequest({
          limit: 10,
          searchAfter: i == 1 ? undefined : requests.at(-1)?.id,
        })
        if (i == activePage && resp.data) setRequests(resp.data.requests)
      }
    }

    fetchData()
  }, [activePage])

  return (
    <Card>
      {requests.map((request) => (
        <Card key={request.id}>
          <Text>{request.id}</Text>
        </Card>
      ))}
      <Pagination value={activePage} onChange={setPage} size="xs" total={10} />
    </Card>
  )
}
