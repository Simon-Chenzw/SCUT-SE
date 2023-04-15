import { useUserInfo } from "@/lib/hook/user-info"
import {
  ActionIcon,
  Button,
  Container,
  createStyles,
  Group,
  Header,
  rem,
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
  }
})

export default function AppHeader() {
  const { classes, theme } = useStyles()
  const { t } = useTranslation()
  const router = useRouter()
  const [userInfo, authApi] = useUserInfo()

  return (
    <Header height={rem("60")} className={classes.header}>
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
    </Header>
  )
}
