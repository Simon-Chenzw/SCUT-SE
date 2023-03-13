import { loginRequest, LoginRequest } from "@/lib/api/login"
import { logoutRequest } from "@/lib/api/logout"
import { MeInfo, meRequest } from "@/lib/api/me"
import { RegisterRequest, registerRequest } from "@/lib/api/register"
import { useState } from "react"

interface UserInfoApi {
  getInfo: () => Promise<void>
  register: (payload: RegisterRequest) => Promise<void>
  login: (payload: LoginRequest) => Promise<void>
  logout: () => Promise<void>
}

export type UserInfo = MeInfo | null

export function useUserInfo(): [MeInfo | null, UserInfoApi] {
  const [info, setInfo] = useState<MeInfo | null>(null)

  const getInfo = async () => {
    const info = await meRequest()
    setInfo(info.data ?? null)
  }

  const register = async (payload: RegisterRequest) => {
    await registerRequest(payload)
    await getInfo()
  }

  const login = async (payload: LoginRequest) => {
    await loginRequest(payload)
    await getInfo()
  }

  const logout = async () => {
    await logoutRequest()
    await getInfo()
  }

  return [info, { getInfo, register, login, logout }]
}
