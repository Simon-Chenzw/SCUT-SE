import { MantineProvider } from "@mantine/core"
import { appWithTranslation } from "next-i18next"
import { AppProps } from "next/app"
import Head from "next/head"

export function App(props: AppProps) {
  const { Component, pageProps } = props

  return (
    <>
      <Head>
        <title>Page title</title>
        <meta
          name="viewport"
          content="minimum-scale=1, initial-scale=1, width=device-width"
        />
      </Head>

      <MantineProvider
        withGlobalStyles
        withNormalizeCSS
        theme={{
          /** Put your mantine theme override here */
          colorScheme: "light",
        }}
      >
        <Component {...pageProps} />
      </MantineProvider>
    </>
  )
}

export default appWithTranslation(App)
