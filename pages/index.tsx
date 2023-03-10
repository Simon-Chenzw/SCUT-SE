import AuthenticationForm from "@/components/authentication"
import UserInfo from "@/components/userinfo"
import {
  AppShell,
  Container,
  Group,
  Header,
  Title,
  useMantineTheme,
} from "@mantine/core"

export default function AppShellDemo() {
  const theme = useMantineTheme()

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
      header={
        <Header height={60}>
          <Group sx={{ height: "100%" }} px={20} position="right" spacing="xs">
            <UserInfo />
          </Group>
        </Header>
      }
    >
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
      <AuthenticationForm />
    </AppShell>
  )
}
