import { MeInfo } from "@/lib/api/auth/me"
import { Button, Text } from "@mantine/core"
import { IconLogout } from "@tabler/icons-react"

export default function UserInfo(props: {
  userInfo?: MeInfo
  onLogout: () => void
}) {
  return (
    <>
      <Text c="blue">
        {props.userInfo !== undefined ? props.userInfo.name : "未登录"}
      </Text>

      {props.userInfo && (
        <Button
          leftIcon={<IconLogout />}
          variant="outline"
          radius="md"
          onClick={props.onLogout}
        >
          登出
        </Button>
      )}
    </>
  )
}
