import AppHeader from "@/components/header"
import RequestDetail from "@/components/request/detail"
import { AppShell, Card, useMantineTheme } from "@mantine/core"
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
  const theme = useMantineTheme()
  const router = useRouter()

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
      <Card>
        <RequestDetail rid={router.query.rid as string} />
      </Card>
    </AppShell>
  )
}
