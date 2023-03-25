import { RequestListObject, requestListRequest } from "@/lib/api/request/list"
import { ActionIcon, Card, Group, Text } from "@mantine/core"
import { useListState } from "@mantine/hooks"
import { IconArrowBarToUp, IconId, IconRefresh } from "@tabler/icons-react"
import { DataTable } from "mantine-datatable"
import Link from "next/link"
import { useEffect, useRef, useState } from "react"

export default function RequestInfo() {
  const batchSize = 15
  const [loading, setLoading] = useState(false)
  const [total, setTotal] = useState(0)
  const [requests, setRequests] = useListState<RequestListObject>([])
  const scrollViewportRef = useRef<HTMLDivElement>(null)

  const reset = async () => {
    const resp = await requestListRequest({
      limit: batchSize,
    })
    if (resp.data) {
      setTotal(resp.data.count)
      setRequests.setState(resp.data.requests)
    }
    scrollViewportRef.current?.scrollTo(0, 0)
  }

  const loadMore = async () => {
    setLoading(true)
    const resp = await requestListRequest({
      limit: batchSize,
      searchAfter: requests.at(-1)?.id,
    })
    if (resp.data) {
      setTotal(resp.data.count)
      for (const req of resp.data.requests) setRequests.append(req)
    }
    setLoading(false)
  }

  useEffect(() => {
    reset()
  }, [])

  return (
    <Card>
      <DataTable
        height={500}
        columns={[
          {
            accessor: "createAt",
            width: 80,
            render: (request: RequestListObject) => {
              new Intl.RelativeTimeFormat(undefined, {
                numeric: "auto",
              })
              return <Text>{new Date(request.createdAt).toLocaleString()}</Text>
            },
          },
          {
            accessor: "status",
            width: 60,
            render: (request: RequestListObject) => {
              if (request.image === null) {
                return <Text>待上传</Text>
              } else if (request.machinedResult === null) {
                return <Text>等待生成</Text>
              } else {
                return <Text>已生成</Text>
              }
            },
          },
          {
            accessor: "link",
            width: 30,
            render: (request: RequestListObject) => {
              return (
                <ActionIcon component={Link} href={`/request/${request.id}`}>
                  <IconId />
                </ActionIcon>
              )
            },
          },
        ]}
        records={requests}
        fetching={loading}
        onScrollToBottom={loadMore}
        scrollViewportRef={scrollViewportRef}
      />
      <Group mt="sm" mx="xs" position="apart">
        <Text size="sm">
          {requests.length}/{total}
        </Text>
        <ActionIcon variant="light" onClick={reset}>
          {requests.length == batchSize ? (
            <IconRefresh />
          ) : (
            <IconArrowBarToUp />
          )}
        </ActionIcon>
      </Group>
    </Card>
  )
}
