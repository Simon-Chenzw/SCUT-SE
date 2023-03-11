import { logoutRequest } from "@/lib/api/logout"
import { meRequest } from "@/lib/api/me"
import { Button, Text } from "@mantine/core"
import { useToggle } from "@mantine/hooks"
import { IconLogout } from "@tabler/icons-react"
import { useEffect, useState } from "react"

export default function UserInfo() {
  const [type, setType] = useToggle(["unauthenticated", "authenticated"])
  const [name, setName] = useState("UserName")
  const [onLogout, setOnLogout] = useToggle([false, true])

  // get info
  useEffect(() => {
    async function getInfo() {
      const info = await meRequest()
      if (info.data) {
        setName(info.data.name)
        setType("authenticated")
      } else {
        setType("unauthenticated")
      }
    }

    getInfo()
  }, [setType])

  // logout
  const logout = async () => {
    setOnLogout(true)
    await logoutRequest()
    setOnLogout(false)
    setType("unauthenticated")
  }

  return (
    <>
      <Text c="blue"> {type === "authenticated" ? name : "未登录"} </Text>
      {type === "authenticated" && (
        <Button
          leftIcon={<IconLogout size="1rem" />}
          variant="outline"
          radius="md"
          onClick={logout}
          loading={onLogout}
        >
          登出
        </Button>
      )}
    </>
  )
}
