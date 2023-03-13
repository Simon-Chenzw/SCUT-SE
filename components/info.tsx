import { Button, Container, Divider, Group, Paper, Title } from "@mantine/core"

export default function AuthenticationForm() {
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
        <Group position="center">
          <Button> upload image </Button>
        </Group>
        <Divider my="lg" />
        <Group position="center">
          <Button> view report </Button>
        </Group>
      </Paper>
    </>
  )
}
