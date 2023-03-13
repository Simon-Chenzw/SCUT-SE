import AuthenticationForm from "@/components/authentication"
import Info from "@/components/info"
import UserInfo from "@/components/userinfo"
import { useUserInfo } from "@/lib/auth-hook"
import { AppShell, Group, Header, useMantineTheme } from "@mantine/core"
import { useEffect } from "react"

export default function AppShellDemo() {
  const theme = useMantineTheme()

  const [userInfo, authApi] = useUserInfo()

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
      {!userInfo ? (
        <AuthenticationForm
          onRegister={authApi.register}
          onLogin={authApi.login}
        />
      ) : (
        <Info />
      )}
    </AppShell>
  )
}
