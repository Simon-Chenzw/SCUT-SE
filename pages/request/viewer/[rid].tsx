import RequestImageViewer from "@/components/request/viewer"
import UserInfo from "@/components/userinfo"
import { useRequest } from "@/lib/hook/request"
import { useUserInfo } from "@/lib/hook/user-info"
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

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()
  const [request] = useRequest(router.query.rid as string)

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
            href={`/request/${router.query.rid as string}`}
            leftIcon={<IconError404 />}
          >
            报告异常 返回详情页
          </Button>
        </Center>
      )}
    </AppShell>
  )
}
