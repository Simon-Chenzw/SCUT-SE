import db from "./db"
import * as api_website from "./api_website"
import { URLDesc } from "./typing"

export function select_all(): URLDesc[] {
  return db.prepare("select * from url").all()
}

export function select(url: string): URLDesc | undefined {
  return db.prepare("select * from url where url = ?").get(url)
}

export function insert(url: string): boolean {
  try {
    const hostname = new URL(url).hostname
    const scripts = api_website.select_host(hostname)
    if (scripts !== undefined) {
      const stmt = db.prepare(
        "INSERT INTO url (url, name, last_update) values (?, ?, ?)"
      )
      stmt.run(url, scripts, 0)
      return true
    }
    return false
  } catch (error) {
    return false
  }
}

export function remove(url: string): void {
  db.prepare("delete from url where url = ?").run(url)
}

export function exec(url: string): void {
  // TODO
  console.log("exec" + url)
}

export function exec_all(): void {
  // TODO
  console.log("exec all")
}
