import { LoginRequest } from "@/lib/api/auth/login"
import { RegisterRequest } from "@/lib/api/auth/register"
import {
  Anchor,
  Button,
  Container,
  Divider,
  Group,
  Paper,
  PasswordInput,
  Stack,
  Text,
  TextInput,
  Title,
} from "@mantine/core"
import { useForm } from "@mantine/form"
import { useToggle } from "@mantine/hooks"
import { useTranslation } from "next-i18next"

export default function AuthenticationForm(props: {
  onRegister: (payload: RegisterRequest) => void
  onLogin: (payload: LoginRequest) => void
}) {
  const { t } = useTranslation()
  const [type, toggle] = useToggle(["login", "register"])
  const form = useForm({
    initialValues: {
      name: "",
      email: "",
      password: "",
      password_repeat: "",
    },

    validate: {
      name: (val) =>
        type !== "register" || val.length <= 50
          ? null
          : t("auth.valid.name_too_long"),
      email: (val) =>
        /^\S+@\S+$/.test(val) ? null : t("auth.valid.email_not_valid"),
      password: (val) =>
        val.length >= 6 ? null : t("auth.valid.password_too_short"),
      password_repeat: (val, values) =>
        type !== "register" || val === values.password
          ? null
          : t("auth.valid.password_not_match"),
    },

    validateInputOnBlur: true,
  })

  const onSubmit = async (values: typeof form.values) => {
    if (type === "login") props.onLogin(values)
    else if (type === "register") props.onRegister(values)
  }

  return (
    <>
      <Container size={420} my={40}>
        <Title
          align="center"
          sx={(theme) => ({
            fontFamily: `Greycliff CF, ${theme.fontFamily}`,
            fontWeight: 900,
          })}
        >
          Welcome back!
        </Title>
      </Container>
      <Paper radius="md" p="xl" withBorder>
        <Text size="lg" weight={500}>
          {type === "login"
            ? t("auth.prompt.login")
            : t("auth.prompt.register")}
        </Text>

        <Group grow mb="md" mt="md">
          <Button />
        </Group>

        <Divider
          label={t("auth.prompt.login_with_email")}
          labelPosition="center"
          my="lg"
        />

        <form onSubmit={form.onSubmit(onSubmit)}>
          <Stack>
            {type === "register" && (
              <TextInput
                required
                label={t("auth.label.name")}
                placeholder="Your username"
                autoComplete="name"
                {...form.getInputProps("name")}
                radius="md"
              />
            )}

            <TextInput
              required
              label={t("auth.label.email")}
              placeholder="email@example.com"
              autoComplete="email"
              {...form.getInputProps("email")}
              radius="md"
            />

            <PasswordInput
              required
              label={t("auth.label.password")}
              placeholder="Your password"
              autoComplete={
                type === "register" ? "new-password" : "current-password"
              }
              {...form.getInputProps("password")}
              radius="md"
            />

            {type === "register" && (
              <PasswordInput
                required
                label={t("auth.label.password_confirm")}
                placeholder="Repeat your password"
                autoComplete="new-password"
                {...form.getInputProps("password_repeat")}
                radius="md"
              />
            )}
          </Stack>

          <Group position="apart" mt="xl">
            <Anchor
              component="button"
              type="button"
              color="dimmed"
              onClick={() => toggle()}
              size="xs"
            >
              {type === "login"
                ? t("auth.prompt.change_to_register")
                : t("auth.prompt.change_to_login")}
            </Anchor>
            <Button type="submit" radius="xl">
              {type === "login"
                ? t("auth.label.login")
                : t("auth.label.register")}
            </Button>
          </Group>
        </form>
      </Paper>
    </>
  )
}
