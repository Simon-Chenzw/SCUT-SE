export async function wechatAppidRequest(): Promise<string> {
  const resp = await fetch("/api/auth/wechat/appid")
  return await resp.text()
}
