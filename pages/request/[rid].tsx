import RequestDetail from "@/components/request/detail"
import UserInfo from "@/components/userinfo"
import { useUserInfo } from "@/lib/hook/user-info"
import { AppShell, Card, Group, Header, useMantineTheme } from "@mantine/core"
import { useRouter } from "next/router"

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()

  return (
    <AppShell
      styles={{
        main: {
          background:
            theme.colorScheme === "dark"
              ? theme.colors.dark[8]
              : theme.colors.gray[0],
        },
      }}
      header={
        <Header height={60}>
          <Group sx={{ height: "100%" }} px={20} position="right" spacing="xs">
            <UserInfo userInfo={userInfo} onLogout={authApi.logout} />
          </Group>
        </Header>
      }
    >
      <Card>
        <RequestDetail rid={router.query.rid as string} />
      </Card>
    </AppShell>
  )
}
