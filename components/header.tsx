import UserInfo from "@/components/userinfo"
import { MeInfo } from "@/lib/api/auth/me"
import { UserInfoApi } from "@/lib/hook/user-info"
import { ActionIcon, Container, Group } from "@mantine/core"
import { IconHome } from "@tabler/icons-react"

export default function AppHeader(props: {
  userInfo?: MeInfo
  authApi?: UserInfoApi
}) {
  return (
    <Container
      fluid
      h={"100%"}
      px="0"
      display="flex"
      style={{
        justifyContent: "space-between",
        alignItems: "center",
      }}
    >
      <Group sx={{ height: "100%" }} px={20} position="left" spacing="xs">
        <ActionIcon variant="transparent" color={"blue"}>
          <IconHome />
        </ActionIcon>
      </Group>
      <Group sx={{ height: "100%" }} px={20} position="right" spacing="xs">
        <UserInfo userInfo={props.userInfo} onLogout={props.authApi?.logout} />
      </Group>
    </Container>
  )
}
