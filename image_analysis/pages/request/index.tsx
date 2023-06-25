import AreaScoreChart from "@/components/chart/area-score"
import ChartPageWrapper from "@/components/chart/wrapper"
import AppHeader from "@/components/header"
import RequestInfo from "@/components/request-info"
import { AppShell, Tabs, useMantineTheme } from "@mantine/core"
import { useToggle } from "@mantine/hooks"
import { IconChartLine, IconList } from "@tabler/icons-react"
import { useTranslation } from "next-i18next"
import { serverSideTranslations } from "next-i18next/serverSideTranslations"

export async function getStaticProps(props: { locale: string }) {
  return {
    props: {
      ...(await serverSideTranslations(props.locale, ["common"])),
    },
  }
}

export default function AppShellDemo() {
  const theme = useMantineTheme()
  const { t } = useTranslation()
  const [tab, setTab] = useToggle(["list", "chart"])

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
              <Tabs.Tab value="list" icon={<IconList size="1.2rem" />}>
                {t("request.tab.list")}
              </Tabs.Tab>
              <Tabs.Tab value="chart" icon={<IconChartLine size="1.2rem" />}>
                {t("request.tab.chart")}
              </Tabs.Tab>
            </>
          }
          defaultTab="list"
          onTabChange={setTab}
        />
      }
    >
      {tab == "list" && <RequestInfo />}
      {tab == "chart" && (
        <ChartPageWrapper title={t("chart.area_score.title")}>
          <AreaScoreChart />
        </ChartPageWrapper>
      )}
    </AppShell>
  )
}
