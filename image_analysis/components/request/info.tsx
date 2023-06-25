import { imageUploadToRequest } from "@/lib/api/image/upload"
import { RequestObject } from "@/lib/api/request"
import { Image, Text, Timeline, TimelineItem, Tooltip } from "@mantine/core"
import { IconPlus } from "@tabler/icons-react"
import { useTranslation } from "next-i18next"
import { useEffect, useState } from "react"
import RequestImageUploader from "./image-upload"

function TimeDisplay(props: { time: Date }) {
  const time = new Date(props.time)
  return (
    <Text size="xs" color="dimmed">
      {time.toLocaleString()}
    </Text>
  )
}

export default function RequestInfo(props: {
  request: RequestObject
  refreshRequest: () => void
}) {
  const { t } = useTranslation()
  const [active, setActive] = useState(1)

  useEffect(() => {
    if (props.request === undefined) setActive(-1)
    else if (props.request.image == null) setActive(0)
    else if (props.request.machinedResult == null) setActive(1)
    else setActive(2)
  }, [props.request])

  return (
    <Timeline active={active} bulletSize={24} lineWidth={3}>
      <TimelineItem
        bullet={<IconPlus size={12} />}
        title={t("request.stage.create")}
        lineVariant={active > 0 ? "solid" : "dashed"}
      >
        <Text color="dimmed" size="sm">
          {props.request.id}
        </Text>
        <TimeDisplay time={props.request.createdAt} />
      </TimelineItem>

      <TimelineItem
        bullet={<IconPlus size={12} />}
        title={t("request.stage.upload")}
        lineVariant={active > 1 ? "solid" : "dashed"}
      >
        {props.request.image == null ? (
          <RequestImageUploader
            onImageUpload={async (file: File) => {
              await imageUploadToRequest(props.request.id, file)
              await props.refreshRequest()
            }}
          />
        ) : (
          <Image
            height={240}
            fit="contain"
            src={`/api/image/${props.request.image.id}`}
            withPlaceholder
            alt="request image"
            caption={
              <Tooltip label={props.request.image.id}>
                <Text> {t("request.status.upload_done")} </Text>
              </Tooltip>
            }
          ></Image>
        )}
      </TimelineItem>

      <TimelineItem
        bullet={<IconPlus size={12} />}
        title={t("request.stage.report")}
        lineVariant={active > 2 ? "solid" : "dashed"}
      >
        {props.request.machinedResult == null ? (
          <Text color="dimmed" size="sm">
            {t("request.status.report_not_found")}
          </Text>
        ) : (
          <>
            <Text color="dimmed" size="sm">
              {t("request.status.done")}
            </Text>
            <TimeDisplay time={props.request.createdAt} />
          </>
        )}
      </TimelineItem>
    </Timeline>
  )
}
