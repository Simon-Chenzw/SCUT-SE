import { JsonApiRequest, JsonApiResponse } from "@/lib/api"
import {
  WechatLoginRequest,
  WechatLoginResponse,
} from "@/lib/api/auth/wechat/login"
import { isJsonRequestOrSetResponse } from "@/lib/api/helper"
import { setTokenCookie } from "@/lib/api/helper/token"
import Token from "@/lib/auth"
import prisma from "@/lib/prisma"
import { WECHAT_APP_ID, WECHAT_APP_SECRET } from "@/lib/wechat"

////////////////////////////////////////////////////////////////////////////////
// lib for wechat

interface WechatAccessTokenResponse {
  access_token: string
  expires_in: number
  refresh_token: string
  openid: string
  scope: string
  is_snapshotuser: number
  unionid?: string
}

interface WechatUserInfoResponse {
  openid: string
  nickname: string
  sex: number
  province: string
  city: string
  country: string
  headimgurl: string
  privilege: unknown
  unionid?: string
}

async function getAccessToken(code: string) {
  const url = new URL("https://api.weixin.qq.com/sns/oauth2/access_token")
  url.search = new URLSearchParams({
    appid: WECHAT_APP_ID,
    secret: WECHAT_APP_SECRET,
    code: code,
    grant_type: "authorization_code",
  }).toString()
  const resp = await fetch(url)
  const data: WechatAccessTokenResponse = await resp.json()
  console.log("access_token", data)
  return { access_token: data.access_token, openid: data.openid }
}

async function getUserInfo(openid: string, access_token: string) {
  const url = new URL("https://api.weixin.qq.com/sns/userinfo")
  url.search = new URLSearchParams({
    lang: "zh_CN",
    openid: openid,
    access_token: access_token,
  }).toString()
  const resp = await fetch(url)
  const data: WechatUserInfoResponse = await resp.json()
  console.log("userinfo", data)
  return { openid: data.openid, nickname: data.nickname }
}

////////////////////////////////////////////////////////////////////////////////

export default async function handler(
  req: JsonApiRequest<WechatLoginRequest>,
  res: JsonApiResponse<WechatLoginResponse>
) {
  if (!isJsonRequestOrSetResponse(req, res)) return

  const { code } = req.body
  const { access_token, openid } = await getAccessToken(code)

  // login
  const cur_account = await prisma.wechatAccount.findUnique({
    where: { openid: openid },
    include: { user: true },
  })
  if (cur_account !== null && cur_account.user !== null) {
    setTokenCookie(req, res, new Token(cur_account.user.id))
    return res.status(200).json({ code: 0, message: "ok" })
  }

  // register
  const { nickname } = await getUserInfo(openid, access_token)
  const new_user = await prisma.user.create({
    data: {
      name: nickname,
      WechatAccount: {
        create: { openid: openid },
      },
    },
  })
  setTokenCookie(req, res, new Token(new_user.id))
  return res.status(200).json({ code: 0, message: "ok" })
}
