import { Box, Center, Divider, Title } from "@mantine/core"
import { ReactNode } from "react"

export default function ChartPageWrapper(props: {
  title: string
  children: ReactNode
}) {
  return (
    <>
      <Center p="md">
        <Title> {props.title} </Title>
      </Center>

      <Divider />
      <Center py="md" h="70vh">
        <Box w="100%" h="auto" mah="70vh" style={{ aspectRatio: 16 / 9 }}>
          {props.children}
        </Box>
      </Center>
    </>
  )
}
