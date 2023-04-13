import AppHeader from "@/components/header"
import RequestImageViewer from "@/components/request/viewer"
import { useRequest } from "@/lib/hook/request"
import { useUserInfo } from "@/lib/hook/user-info"
import {
  AppShell,
  Button,
  Center,
  Header,
  Loader,
  useMantineTheme,
} from "@mantine/core"
import { IconError404 } from "@tabler/icons-react"
import { useTranslation } from "next-i18next"
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
  const { t } = useTranslation()
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
          <AppHeader userInfo={userInfo} authApi={authApi} />
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
            {t("request.action.error_return_to_detail")}
          </Button>
        </Center>
      )}
    </AppShell>
  )
}
