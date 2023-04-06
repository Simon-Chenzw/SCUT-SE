import { imageUploadToRequest } from "@/lib/api/image/upload"
import { useRequest } from "@/lib/hook/request"
import {
  Button,
  Card,
  Image,
  Skeleton,
  Text,
  Timeline,
  TimelineItem,
  Tooltip,
} from "@mantine/core"
import { IconMan, IconPlus } from "@tabler/icons-react"
import Link from "next/link"
import { useEffect, useState } from "react"
import RequestImageUploader from "./image-upload"

function RequestDetailSkeleton() {
  return (
    <>
      <Skeleton height={50} circle mb="xl" />
      <Skeleton height={8} radius="xl" />
      <Skeleton height={8} mt={6} radius="xl" />
      <Skeleton height={8} mt={6} width="70%" radius="xl" />
    </>
  )
}

function TimeDisplay(props: { time: Date }) {
  const time = new Date(props.time)
  return (
    <Text size="xs" color="dimmed">
      {time.toLocaleString()}
    </Text>
  )
}

export default function RequestDetail(props: { rid: string }) {
  const [request, updateRequest] = useRequest(props.rid)
  const [active, setActive] = useState(1)

  useEffect(() => {
    if (request === undefined) setActive(-1)
    else if (request.image == null) setActive(0)
    else if (request.machinedResult == null) setActive(1)
    else setActive(2)
  }, [request])

  if (request === undefined) {
    return <RequestDetailSkeleton />
  } else {
    return (
      <Timeline active={active} bulletSize={24} lineWidth={3}>
        <TimelineItem
          bullet={<IconPlus size={12} />}
          title="创建报告"
          lineVariant={active > 0 ? "solid" : "dashed"}
        >
          <Text color="dimmed" size="sm">
            {request.id}
          </Text>
          <TimeDisplay time={request.createdAt} />
        </TimelineItem>

        <TimelineItem
          bullet={<IconPlus size={12} />}
          title="上传图片"
          lineVariant={active > 1 ? "solid" : "dashed"}
        >
          {request.image == null ? (
            <RequestImageUploader
              onImageUpload={async (file: File) => {
                await imageUploadToRequest(props.rid, file)
                await updateRequest()
              }}
            />
          ) : (
            <Image
              height={240}
              fit="contain"
              src={`/api/image/${request.image.id}`}
              withPlaceholder
              alt="request image"
              caption={
                <Tooltip label={request.image.id}>
                  <Text> 已上传图片 </Text>
                </Tooltip>
              }
            ></Image>
          )}
        </TimelineItem>

        <TimelineItem
          bullet={<IconPlus size={12} />}
          title="生成报告"
          lineVariant={active > 2 ? "solid" : "dashed"}
        >
          {request.machinedResult == null ? (
            <Text color="dimmed" size="sm">
              尚未生成报告
            </Text>
          ) : (
            <>
              <Card>
                <Button
                  variant="light"
                  component={Link}
                  href={`/request/viewer/${request.id}`}
                  leftIcon={<IconMan />}
                >
                  查看报告
                </Button>
              </Card>
              <TimeDisplay time={request.createdAt} />
            </>
          )}
        </TimelineItem>
      </Timeline>
    )
  }
}
