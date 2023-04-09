import RequestImageViewerItem from "@/components/request/viewer-item"
import UserInfo from "@/components/userinfo"
import { MachinedResultObject } from "@/lib/api/request"
import { useImage } from "@/lib/hook/image"
import { useRequest } from "@/lib/hook/request"
import { useUserInfo } from "@/lib/hook/user-info"
import {
  AppShell,
  Button,
  Center,
  Group,
  Header,
  Loader,
  Stack,
  useMantineTheme,
} from "@mantine/core"
import { IconError404 } from "@tabler/icons-react"
import { serverSideTranslations } from "next-i18next/serverSideTranslations"
import Link from "next/link"
import { useRouter } from "next/router"

export async function getStaticPaths() {
  return {
    paths: [],
    fallback: "blocking",
  }
}

export async function getStaticProps(props: { locale: string }) {
  return {
    props: {
      ...(await serverSideTranslations(props.locale, ["common"])),
    },
  }
}

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()
  const [request] = useRequest(router.query.rid as string)
  const image = useImage(request?.image ?? null)

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
      ) : request.image &&
        request.machinedResult &&
        request.machinedResult.data ? (
        <Center>
          <Stack>
            {(
              request.machinedResult.data as unknown as MachinedResultObject[]
            ).map((obj, index) => (
              <RequestImageViewerItem key={index} image={image} object={obj} />
            ))}
          </Stack>
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