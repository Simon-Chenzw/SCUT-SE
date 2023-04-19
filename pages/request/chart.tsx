import AreaScoreChart from "@/components/chart/area-score"
import AppHeader from "@/components/header"
import {
  AppShell,
  Box,
  Center,
  Divider,
  Title,
  useMantineTheme,
} from "@mantine/core"
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
      header={<AppHeader />}
    >
      <Center p="md">
        <Title> {t("chart.area_score.title")} </Title>
      </Center>

      <Divider />
      <Center py="md" h="70vh">
        <Box w="100%" h="auto" style={{ aspectRatio: 16 / 9 }}>
          <AreaScoreChart />
        </Box>
      </Center>
    </AppShell>
  )
}
