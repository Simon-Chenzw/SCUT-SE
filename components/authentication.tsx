import { loginRequest } from "@/lib/api/login"
import { registerRequest } from "@/lib/api/register"
import {
  Anchor,
  Button,
  Divider,
  Group,
  Paper,
  PasswordInput,
  Stack,
  Text,
  TextInput,
} from "@mantine/core"
import { useForm } from "@mantine/form"
import { useToggle } from "@mantine/hooks"

export default function AuthenticationForm() {
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
        type !== "register" || val.length <= 50 ? null : "名称最长 50 个字符",
      email: (val) => (/^\S+@\S+$/.test(val) ? null : "邮箱地址格式不正常"),
      password: (val) => (val.length >= 6 ? null : "密码需要至少 6 个字符"),
      password_repeat: (val, values) =>
        type !== "register" || val === values.password ? null : "密码不一致",
    },

    validateInputOnBlur: true,
  })

  const onSubmit = async (values: typeof form.values) => {
    if (type === "login") {
      await loginRequest(values)
    } else if (type === "register") {
      await registerRequest(values)
    }
  }

  return (
    <Paper radius="md" p="xl" withBorder>
      <Text size="lg" weight={500}>
        {type === "login" ? "请进行登录，以继续：" : "请进行注册，以继续："}
      </Text>

      <Group grow mb="md" mt="md">
        <Button />
      </Group>

      <Divider label="或者 使用邮箱登录" labelPosition="center" my="lg" />

      <form onSubmit={form.onSubmit(onSubmit)}>
        <Stack>
          {type === "register" && (
            <TextInput
              required
              label="名称"
              placeholder="Your username"
              {...form.getInputProps("name")}
              radius="md"
            />
          )}

          <TextInput
            required
            label="邮箱"
            placeholder="email@example.com"
            {...form.getInputProps("email")}
            radius="md"
          />

          <PasswordInput
            required
            label="密码"
            placeholder="Your password"
            {...form.getInputProps("password")}
            radius="md"
          />

          {type === "register" && (
            <PasswordInput
              required
              label="重复密码"
              placeholder="Repeat your password"
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
              ? "还没有账户? 点击注册"
              : "已经有了账户? 点击登录"}
          </Anchor>
          <Button type="submit" radius="xl">
            {type === "login" ? "登录" : "注册"}
          </Button>
        </Group>
      </form>
    </Paper>
  )
}
