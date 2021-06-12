import db from "./db"
import type { FundInfo } from "./typing"
import { ipcRenderer } from "electron"

export function exec(url: string): void {
  ipcRenderer.send("exec-start", url)
}

export function exec_all(): void {
  const urls = db
    .prepare(
      "select url from website natural join url where script is not null"
    )
    .all()
  for (const { url } of urls) ipcRenderer.send("exec-start", url)
}

export function set_exec_callback(
  callback: (resp: { url: string; status: boolean; err?: Error }) => void
): void {
  ipcRenderer.on("exec-end", (event, arg) => {
    callback(arg)
  })
}

export function rm_exec_callback(): void {
  ipcRenderer.removeAllListeners("exec-end")
}

export function select(url: string): FundInfo {
  return db.prepare("select * from fund where url = ?").all(url)
}

export function insert(url: string, data: FundInfo): void {
  const clear = db.prepare("delete from fund where url = ?")
  const update_last = db.prepare("update url set last_update = ? where url = ?")
  const stmt = db.prepare("insert into fund values (?,?,?)")
  db.transaction(() => {
    clear.run(url)
    let last_update = 0
    for (const ele of data) {
      stmt.run(url, ele.date, ele.value)
      last_update = Math.max(last_update, ele.date)
    }
    update_last.run(last_update, url)
  })()
}

export function clear(url: string): void {
  db.transaction(() => {
    db.prepare("delete from fund where url = ?").run(url)
    db.prepare("update url set last_update=0 where url = ?").run(url)
  })()
}
