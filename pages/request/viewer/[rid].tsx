import RequestImageViewer from "@/components/request/viewer"
import UserInfo from "@/components/userinfo"
import { useUserInfo } from "@/lib/auth-hook"
import { useRequest } from "@/lib/hook/request"
import {
  AppShell,
  Button,
  Center,
  Group,
  Header,
  Loader,
  useMantineTheme,
} from "@mantine/core"
import { IconError404 } from "@tabler/icons-react"
import Link from "next/link"
import { useRouter } from "next/router"
import { useEffect } from "react"

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()

  const [userInfo, authApi] = useUserInfo()
  const rid = router.query.rid as string
  const [request] = useRequest(rid)

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
      {request === undefined ? (
        <Center h={100}>
          <Loader />
        </Center>
      ) : request.image && request.machinedResult ? (
        <Center h={"80vh"}>
          <RequestImageViewer
            image={request.image}
            machinedResult={request.machinedResult}
          />
        </Center>
      ) : (
        <Center h={100}>
          <Button
            variant="light"
            component={Link}
            href={`/request/${rid}`}
            leftIcon={<IconError404 />}
          >
            报告异常 返回详情页
          </Button>
        </Center>
      )}
    </AppShell>
  )
}
