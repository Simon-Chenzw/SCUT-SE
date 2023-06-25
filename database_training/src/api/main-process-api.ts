import assert from "assert"
import axios from "axios"
import { ipcMain } from "electron"
import vm from "vm"
import * as api_fund from "./api_fund"
import * as api_website from "./api_website"

async function exec_script(url: string): Promise<void> {
  const hostname = new URL(url).hostname
  const code = api_website.get_script_hostname(hostname)
  assert(code !== null, "script in empty")
  const script = new vm.Script(code)
  const ctx = vm.createContext({ require, axios })
  script.runInContext(ctx)
  const ret = await ctx.get(url)
  for (const ele of ret) {
    assert(typeof ele.date === "number", "return type is illegal")
    assert(typeof ele.value === "number", "return type is illegal")
  }
  api_fund.insert(url, ret)
}

export default function register(): void {
  ipcMain.on("exec-start", (event, arg) => {
    exec_script(arg)
      .then(() => {
        event.reply("exec-end", {
          url: arg,
          status: true,
        })
      })
      .catch((err) => {
        event.reply("exec-end", {
          url: arg,
          status: false,
          err: err,
        })
      })
  })
}
