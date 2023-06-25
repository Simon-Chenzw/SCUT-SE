import AuthenticationForm from "@/components/authentication"
import AppHeader from "@/components/header"
import { loginRequest } from "@/lib/api/auth/login"
import { registerRequest } from "@/lib/api/auth/register"
import { AppShell, useMantineTheme } from "@mantine/core"
import { serverSideTranslations } from "next-i18next/serverSideTranslations"
import { useRouter } from "next/router"

export async function getStaticProps(props: { locale: string }) {
  return {
    props: {
      ...(await serverSideTranslations(props.locale, ["common"])),
    },
  }
}

export default function AuthPage() {
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
      <AuthenticationForm
        onRegister={async (payload) => {
          await registerRequest(payload)
          router.push("/")
        }}
        onLogin={async (payload) => {
          await loginRequest(payload)
          router.push("/")
        }}
      />
    </AppShell>
  )
}
