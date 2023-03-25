import UserInfo from "@/components/userinfo"
import { useUserInfo } from "@/lib/auth-hook"
import { AppShell, Group, Header, Text, useMantineTheme } from "@mantine/core"
import { useRouter } from "next/router"
import { useEffect } from "react"

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()

  const [userInfo, authApi] = useUserInfo()
  const { rid } = router.query

  // async init
  useEffect(() => {
    ;(async () => {
      await authApi.getInfo()
    })()
  }, [])

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
      <Text> info of id={rid} </Text>
    </AppShell>
  )
}
