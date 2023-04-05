import {
  ActionIcon,
  Button,
  Card,
  FileButton,
  Group,
  Image,
  Space,
} from "@mantine/core"
import { IconCheck, IconUpload, IconX } from "@tabler/icons-react"
import { useState } from "react"

export default function RequestImageUploader(props: {
  onImageUpload?: (file: File) => void
}) {
  const [file, setFile] = useState<File | null>(null)
  const [fileUrl, setFileUrl] = useState<string | null>(null)

  const changeFile = (file: File | null) => {
    if (file === null) {
      if (fileUrl !== null) URL.revokeObjectURL(fileUrl)
      setFile(null)
      setFileUrl(null)
    } else {
      if (fileUrl !== null) URL.revokeObjectURL(fileUrl)
      setFile(file)
      setFileUrl(URL.createObjectURL(file))
    }
  }

  if (file === null) {
    return (
      <Card>
        <Space></Space>
        <Card.Section>
          <FileButton onChange={changeFile} accept="image/*">
            {(props) => (
              <Button leftIcon={<IconUpload />} {...props}>
                上传图片
              </Button>
            )}
          </FileButton>
        </Card.Section>
      </Card>
    )
  } else {
    return (
      <Card>
        <Card.Section>
          <Image
            height={240}
            fit="contain"
            src={fileUrl}
            withPlaceholder
            alt="thumbnail"
            caption={file.name}
          />
        </Card.Section>
        <Space></Space>
        <Group position="center" spacing="xs">
          <ActionIcon
            variant="filled"
            radius="xl"
            size="xs"
            onClick={() => {
              if (file !== null && props.onImageUpload !== undefined)
                props.onImageUpload(file)
            }}
          >
            <IconCheck size="xs" />
          </ActionIcon>
          <ActionIcon
            variant="outline"
            radius="xl"
            size="xs"
            onClick={() => {
              changeFile(null)
            }}
          >
            <IconX size="xs" />
          </ActionIcon>
        </Group>
      </Card>
    )
  }
}
