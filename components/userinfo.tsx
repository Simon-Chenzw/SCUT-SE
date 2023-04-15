import { MeInfo } from "@/lib/api/auth/me"
import { Button, Text } from "@mantine/core"
import { IconLogout } from "@tabler/icons-react"
import { useTranslation } from "next-i18next"

export default function UserInfo(props: {
  userInfo?: MeInfo
  onLogout?: () => void
}) {
  const { t } = useTranslation()

  return (
    <>
      <Text c="blue">
        {props.userInfo !== undefined ? props.userInfo.name : t("guest")}
      </Text>

      {props.userInfo && (
        <Button
          leftIcon={<IconLogout />}
          variant="outline"
          radius="md"
          onClick={props.onLogout}
        >
          {t("auth.label.logout")}
        </Button>
      )}
    </>
  )
}
