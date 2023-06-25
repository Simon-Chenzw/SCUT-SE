import OrganDiagram from "@/components/chart/organ-diagram"
import ChartPageWrapper from "@/components/chart/wrapper"
import AppHeader from "@/components/header"
import RequestInfo from "@/components/request/info"
import RequestImageViewer from "@/components/request/viewer"
import RequestImageViewerItem from "@/components/request/viewer-item"
import { useImage } from "@/lib/hook/image"
import { useRequest } from "@/lib/hook/request"
import {
  AppShell,
  Card,
  Center,
  Stack,
  Tabs,
  useMantineTheme,
} from "@mantine/core"
import { useToggle } from "@mantine/hooks"
import {
  IconInfoHexagon,
  IconListDetails,
  IconLungs,
  IconPhotoSearch,
} from "@tabler/icons-react"
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
  const [tab, setTab] = useToggle(["info", "viewer", "detail", "diagram"])

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
        <AppHeader
          tabs={
            <>
              <Tabs.Tab value="info" icon={<IconInfoHexagon size="1.2rem" />}>
                {t("request.tab.info")}
              </Tabs.Tab>
              {request && request.image && request.machinedResult && (
                <>
                  <Tabs.Tab
                    value="viewer"
                    icon={<IconPhotoSearch size="1.2rem" />}
                  >
                    {t("request.tab.viewer")}
                  </Tabs.Tab>
                  <Tabs.Tab
                    value="detail"
                    icon={<IconListDetails size="1.2rem" />}
                  >
                    {t("request.tab.detail")}
                  </Tabs.Tab>
                  <Tabs.Tab value="diagram" icon={<IconLungs size="1.2rem" />}>
                    {t("request.tab.diagram")}
                  </Tabs.Tab>
                </>
              )}
            </>
          }
          defaultTab={"info"}
          onTabChange={setTab}
        />
      }
    >
      {tab == "info" && request && (
        <Card>
          <RequestInfo request={request} refreshRequest={refreshRequest} />
        </Card>
      )}
      {tab == "viewer" && request?.machinedResult && (
        <Center h={"80vh"}>
          <RequestImageViewer
            image={image}
            machinedResult={request.machinedResult}
          />
        </Center>
      )}
      {tab == "detail" && request?.machinedResult?.data && (
        <Center>
          <Stack w="100%">
            {request.machinedResult.data.map((obj) => (
              <RequestImageViewerItem
                key={obj["area"]}
                image={image}
                object={obj}
              />
            ))}
          </Stack>
        </Center>
      )}
      {tab == "diagram" && request?.machinedResult && (
        <ChartPageWrapper title={t("chart.organ_diagram.title")}>
          <OrganDiagram machinedResult={request.machinedResult} />
        </ChartPageWrapper>
      )}
    </AppShell>
  )
}
