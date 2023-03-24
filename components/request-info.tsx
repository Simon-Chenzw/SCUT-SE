import { RequestListObject, requestListRequest } from "@/lib/api/request/list"
import { Card, Pagination, Text } from "@mantine/core"
import { useEffect, useState } from "react"

export default function RequestInfo() {
  const [activePage, setPage] = useState(1)
  const [requests, setRequests] = useState<RequestListObject[]>([])

  useEffect(() => {
    const fetchData = async () => {
      const resp = await requestListRequest({
        pagination: {
          limit: 10,
          offset: activePage * 10 - 10,
        },
      })
      if (resp.data) setRequests(resp.data.requests)
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
