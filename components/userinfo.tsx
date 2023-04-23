import { useUserInfo } from "@/lib/hook/user-info"
import {
  Avatar,
  Button,
  Center,
  Loader,
  Paper,
  Space,
  Stack,
  Text,
} from "@mantine/core"
import {
  IconChartLine,
  IconDeviceAnalytics,
  IconList,
} from "@tabler/icons-react"
import { useTranslation } from "next-i18next"
import Link from "next/link"

export default function UserInfo() {
  const { t } = useTranslation()
  const [userInfo] = useUserInfo()

  if (userInfo === undefined)
    return (
      <Center w={"100vw"} h={"100vh"}>
        <Loader />
      </Center>
    )
  else
    return (
      <Paper
        radius="md"
        withBorder
        p="lg"
        sx={(theme) => ({
          backgroundColor:
            theme.colorScheme === "dark" ? theme.colors.dark[8] : theme.white,
        })}
      >
        <Stack h={300}>
          <Avatar src={undefined} size={120} radius={120} mx="auto" />

          <Text ta="center" fz="lg" weight={500} mt="md">
            {userInfo.name}
          </Text>

          <Text ta="center" c="dimmed" fz="sm">
            {userInfo.email}
          </Text>

          <Space />

          <Button
            component={Link}
            href={{
              pathname: "/request",
              query: { t: "list" },
            }}
            leftIcon={<IconList />}
            variant="filled"
          >
            {t("goto.request_list")}
          </Button>
          <Button
            component={Link}
            href={{
              pathname: "/request",
              query: { t: "chart" },
            }}
            leftIcon={<IconChartLine />}
            variant="filled"
          >
            {t("goto.request_charts")}
          </Button>
          {userInfo.role === "ADMIN" && (
            <Button
              component={Link}
              href={`/admin`}
              leftIcon={<IconDeviceAnalytics />}
              variant="filled"
            >
              {t("goto.admin_charts")}
            </Button>
          )}
        </Stack>
      </Paper>
    )
}
