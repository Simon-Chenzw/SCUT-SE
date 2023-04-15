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
import { useRouter } from "next/router"

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
  tabs?: [string, string][]
  tab?: string
  onTabChange?: (tab: string) => void
}) {
  const { classes, theme } = useStyles()
  const { t } = useTranslation()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()

  return (
    <Header
      height={props.tabs && props.tabs.length > 1 ? rem("98") : rem("60")}
      className={classes.header}
    >
      <Container fluid className={classes.mainSection}>
        <Group position="left">
          <ActionIcon variant="subtle" color={theme.primaryColor}>
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
      {props.tabs && props.tabs.length > 1 && (
        <Container fluid className={classes.tabSection}>
          <Tabs
            value={props.tab}
            onTabChange={props.onTabChange}
            variant="outline"
            classNames={{
              tabsList: classes.tabsList,
              tab: classes.tab,
            }}
          >
            <Tabs.List>
              {props.tabs.map((v) => (
                <Tabs.Tab value={v[0]} key={v[0]}>
                  {v[1]}
                </Tabs.Tab>
              ))}
            </Tabs.List>
          </Tabs>
        </Container>
      )}
    </Header>
  )
}
