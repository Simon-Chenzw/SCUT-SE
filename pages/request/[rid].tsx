import AppHeader from "@/components/header"
import RequestInfo from "@/components/request/info"
import RequestImageViewer from "@/components/request/viewer"
import RequestImageViewerItem from "@/components/request/viewer-item"
import { MachinedResultObject } from "@/lib/api/request"
import { useImage } from "@/lib/hook/image"
import { useRequest } from "@/lib/hook/request"
import { useTab } from "@/lib/hook/tab"
import { AppShell, Card, Center, Stack, useMantineTheme } from "@mantine/core"
import { useTranslation } from "next-i18next"
import { serverSideTranslations } from "next-i18next/serverSideTranslations"
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
  const [request, refreshRequest] = useRequest(router.query.rid as string)
  const image = useImage(request?.image ?? null)

  const [tab, setTab, tabs] = useTab([
    ["info", t("request.tab.info")],
    ...(request && request.image && request.machinedResult
      ? ([
          ["viewer", t("request.tab.viewer")],
          ["detail", t("request.tab.detail")],
        ] as [string, string][])
      : []),
  ])

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
      header={<AppHeader {...{ tab, onTabChange: setTab, tabs }} />}
    >
      {tab == "info" && request ? (
        <Card>
          <RequestInfo request={request} refreshRequest={refreshRequest} />
        </Card>
      ) : tab == "viewer" && request?.machinedResult ? (
        <Center h={"80vh"}>
          <RequestImageViewer
            image={image}
            machinedResult={request.machinedResult}
          />
        </Center>
      ) : tab == "detail" && request?.machinedResult?.data ? (
        <Center>
          <Stack>
            {(
              request.machinedResult.data as unknown as MachinedResultObject[]
            ).map((obj) => (
              <RequestImageViewerItem
                key={obj["area"]}
                image={image}
                object={obj}
              />
            ))}
          </Stack>
        </Center>
      ) : (
        <></>
      )}
    </AppShell>
  )
}
