import { loginRequest, LoginRequest } from "@/lib/api/auth/login"
import { logoutRequest } from "@/lib/api/auth/logout"
import { MeInfo, meRequest } from "@/lib/api/auth/me"
import { RegisterRequest, registerRequest } from "@/lib/api/auth/register"
import { useEffect, useState } from "react"

export type UserInfo = MeInfo | null

export interface UserInfoApi {
  getInfo: () => Promise<void>
  register: (payload: RegisterRequest) => Promise<void>
  login: (payload: LoginRequest) => Promise<void>
  logout: () => Promise<void>
}

export function useUserInfo(): [MeInfo | undefined, UserInfoApi] {
  const [info, setInfo] = useState<MeInfo>()

  const getInfo = async () => {
    const info = await meRequest()
    setInfo(info.data)
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

  useEffect(() => {
    getInfo()
  }, [])

  return [info, { getInfo, register, login, logout }]
}
