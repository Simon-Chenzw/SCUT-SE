import UserCreateAggChart from "@/components/chart/user-create-agg"
import ChartPageWrapper from "@/components/chart/wrapper"
import AppHeader from "@/components/header"
import { AppShell, Tabs, useMantineTheme } from "@mantine/core"
import { useToggle } from "@mantine/hooks"
import { IconUser } from "@tabler/icons-react"
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
  const [tab, setTab] = useToggle(["user_create_agg"])

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
              <Tabs.Tab
                value="user_create_agg"
                icon={<IconUser size="1.2rem" />}
              >
                {t("admin.tab.user_create_agg")}
              </Tabs.Tab>
            </>
          }
          defaultTab="user_create_agg"
          onTabChange={setTab}
        />
      }
    >
      {tab == "user_create_agg" && (
        <ChartPageWrapper title={t("chart.user_create_agg.title")}>
          <UserCreateAggChart />
        </ChartPageWrapper>
      )}
    </AppShell>
  )
}
