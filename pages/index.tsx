import AuthenticationForm from "@/components/authentication"
import AppHeader from "@/components/header"
import RequestInfo from "@/components/request-info"
import { useUserInfo } from "@/lib/hook/user-info"
import { AppShell, Header, useMantineTheme } from "@mantine/core"

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
  const [userInfo, authApi] = useUserInfo()

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
      {!userInfo ? (
        <AuthenticationForm
          onRegister={authApi.register}
          onLogin={authApi.login}
        />
      ) : (
        <RequestInfo />
      )}
    </AppShell>
  )
}
