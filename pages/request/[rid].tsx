import UserInfo from "@/components/userinfo"
import { RequestObject } from "@/lib/api/request"
import { requestGetRequest } from "@/lib/api/request/[rid]"
import { useUserInfo } from "@/lib/auth-hook"
import { AppShell, Group, Header, Text, useMantineTheme } from "@mantine/core"
import { useRouter } from "next/router"
import { useEffect, useState } from "react"

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()

  const [userInfo, authApi] = useUserInfo()
  const [request, setRequest] = useState<RequestObject>()
  const { rid } = router.query as unknown as { rid: string }

  // async init
  useEffect(() => {
    ;(async () => {
      await authApi.getInfo()
    })()
  }, [])

  useEffect(() => {
    ;(async () => {
      const req = await requestGetRequest({ id: rid })
      setRequest(req.data)
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
      <Text> {JSON.stringify(request, undefined, "\t")} </Text>
    </AppShell>
  )
}
