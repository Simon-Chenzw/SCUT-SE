import { useUserInfo } from "@/lib/hook/user-info"
import {
  ActionIcon,
  Button,
  Container,
  createStyles,
  Group,
  Header,
  rem,
  Tabs,
  Text,
} from "@mantine/core"
import { IconHome, IconLogout } from "@tabler/icons-react"
import { useTranslation } from "next-i18next"
import Link from "next/link"
import { useRouter } from "next/router"
import { ReactNode, useEffect, useState } from "react"

const useStyles = createStyles((theme) => {
  return {
    header: {
      backgroundColor: theme.colors.gray[1],
      borderBottom: `${rem(1)} solid ${theme.colors.gray[2]}`,
    },

    mainSection: {
      alignItems: "center",
      display: "flex",
      justifyContent: "space-between",
      paddingLeft: theme.spacing.md,
      paddingRight: theme.spacing.md,
      paddingTop: theme.spacing.sm,
      paddingBottom: theme.spacing.sm,
    },

    tabSection: {
      paddingLeft: theme.spacing.xl,
      paddingRight: theme.spacing.xl,
    },

    tabsList: {
      borderBottom: "0 !important",
    },

    tab: {
      fontWeight: 500,
      height: rem(38),
      backgroundColor: "transparent",
      "&:hover": {
        backgroundColor: theme.colors.gray[1],
      },
      "&[data-active]": {
        backgroundColor: theme.white,
        borderColor: theme.colors.gray[2],
      },
    },
  }
})

export default function AppHeader(props: {
  tabs?: ReactNode
  defaultTab?: string
  onTabChange?: (tab: string) => void
}) {
  const { classes, theme } = useStyles()
  const { t } = useTranslation()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()
  const [tab, setTab] = useState<string | undefined>(props.defaultTab)

  // get tab from router
  useEffect(() => {
    if (!router.isReady) return
    const t = Array.isArray(router.query.t)
      ? router.query.t.at(0)
      : router.query.t
    setTab(t || props.defaultTab)
  }, [router])

  // set tab in router & call props.onTabChange
  const onTabChange = (t: string) => {
    setTab(t)
    if (t === props.defaultTab) {
      // eslint-disable-next-line @typescript-eslint/no-unused-vars
      const { t, ...query } = router.query
      router.push({ query }, undefined, { shallow: true })
    } else {
      const query = { ...router.query, t }
      router.push({ query }, undefined, { shallow: true })
    }
    if (props.onTabChange) props.onTabChange(t)
  }

  return (
    <Header
      height={props.tabs ? rem("98") : rem("60")}
      className={classes.header}
    >
      <Container fluid className={classes.mainSection}>
        <Group position="left">
          <ActionIcon
            component={Link}
            href={`/`}
            variant="subtle"
            color={theme.primaryColor}
          >
            <IconHome />
          </ActionIcon>
        </Group>

        <Group position="right">
          <Text c={theme.primaryColor}>
            {userInfo !== undefined ? userInfo.name : t("guest")}
          </Text>

          {userInfo && (
            <Button
              leftIcon={<IconLogout />}
              variant="outline"
              radius="md"
              onClick={async () => {
                await authApi.logout()
                router.push("/auth")
              }}
              color={theme.primaryColor}
            >
              {t("auth.label.logout")}
            </Button>
          )}
        </Group>
      </Container>
      {props.tabs && (
        <Container fluid className={classes.tabSection}>
          <Tabs
            value={tab}
            onTabChange={onTabChange}
            variant="outline"
            classNames={{
              tabsList: classes.tabsList,
              tab: classes.tab,
            }}
          >
            <Tabs.List>{props.tabs}</Tabs.List>
          </Tabs>
        </Container>
      )}
    </Header>
  )
}
