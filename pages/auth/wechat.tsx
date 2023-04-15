import { wechatAppidRequest } from "@/lib/api/auth/wechat/appid"
import { wechatLoginRequest } from "@/lib/api/auth/wechat/login"
import { WECHAT_COLOR } from "@/lib/wechat"
import { Center, Loader, Space, Stack, Title } from "@mantine/core"
import { useTranslation } from "next-i18next"
import { serverSideTranslations } from "next-i18next/serverSideTranslations"
import { useRouter } from "next/router"
import { useEffect } from "react"

export async function getStaticProps(props: { locale: string }) {
  return {
    props: {
      ...(await serverSideTranslations(props.locale, ["common"])),
    },
  }
}

async function redirectToWechat(state?: string) {
  const url = new URL("https://open.weixin.qq.com/connect/oauth2/authorize")
  url.search = new URLSearchParams({
    appid: await wechatAppidRequest(),
    redirect_uri: window.location.origin + window.location.pathname,
    response_type: "code",
    scope: "snsapi_userinfo",
    ...(state && { state: state }),
  }).toString()
  url.hash = "wechat_redirect"
  window.location.href = url.toString()
}

export default function AuthWechat() {
  const { t } = useTranslation()
  const router = useRouter()

  useEffect(() => {
    if (!router.isReady) return
    const code = Array.isArray(router.query.code)
      ? router.query.code.at(0)
      : router.query.code
    const state = Array.isArray(router.query.state)
      ? router.query.state.at(0)
      : router.query.state
    if (code === undefined) {
      redirectToWechat(state)
    } else {
      wechatLoginRequest({ code, state }).then(() => router.push("/"))
    }
  }, [router])

  return (
    <Center w={"100vw"} h={"100vh"}>
      <Stack>
        <Title
          align="center"
          sx={(theme) => ({
            fontFamily: `Greycliff CF, ${theme.fontFamily}`,
            fontWeight: 900,
            fontSize: "2em",
          })}
        >
          {router.query.code === undefined
            ? t("auth.third_party.wechat.waiting")
            : t("auth.third_party.wechat.logging")}
        </Title>
        <Space />
        <Center>
          <Loader color={WECHAT_COLOR} />
        </Center>
      </Stack>
    </Center>
  )
}
