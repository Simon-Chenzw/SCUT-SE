import { MachinedResultObject } from "@/lib/api/request"
import {
  Card,
  Center,
  Container,
  Divider,
  Grid,
  Stack,
  Text,
} from "@mantine/core"
import { useEffect, useRef } from "react"

function RequestImageViewerItemRegion(props: {
  image: HTMLImageElement | undefined
  object: MachinedResultObject | undefined
}) {
  const ref = useRef<HTMLCanvasElement>(null)

  useEffect(() => {
    if (props.image === undefined || props.object == undefined) return
    const canvas = ref.current
    if (canvas === null) return
    const ctx = canvas.getContext("2d")
    if (ctx === null) return

    canvas.width = props.object.region.w
    canvas.height = props.object.region.h
    ctx.drawImage(
      props.image,
      props.object.region.x,
      props.object.region.y,
      props.object.region.w,
      props.object.region.h,
      0,
      0,
      props.object.region.w,
      props.object.region.h
    )
  }, [ref, props.image, props.object])

  return (
    <canvas
      ref={ref}
      style={{
        maxWidth: "100%",
        maxHeight: "100%",
      }}
    />
  )
}

export default function RequestImageViewerItem(props: {
  image: HTMLImageElement | undefined
  object: MachinedResultObject | undefined
}) {
  return (
    <Card shadow={"md"} withBorder>
      <Grid>
        <Grid.Col span={"auto"}>
          <Stack>
            <Center>
              <Text>area</Text>
            </Center>
            <Divider />
            <Center>
              <Text>{props.object?.area}</Text>
            </Center>
          </Stack>
        </Grid.Col>

        <Grid.Col span={8}>
          <Container>
            <RequestImageViewerItemRegion {...props} />
          </Container>
        </Grid.Col>
      </Grid>

      <Card.Section>
        <Divider
          label={<Text size="md"> message </Text>}
          labelPosition="center"
        />
      </Card.Section>

      <Text> {props.object?.message} </Text>
    </Card>
  )
}
