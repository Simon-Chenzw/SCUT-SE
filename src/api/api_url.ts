import db from "./db"
import type { URLDesc } from "./typing"

export function select_all(): URLDesc[] {
  return db.prepare("select * from url").all()
}

export function select(url: string): URLDesc | null {
  return db.prepare("select * from url where url = ?").get(url)
}

export function insert(url: string): boolean {
  try {
    const hostname = new URL(url).hostname
    const stmt = db.prepare(
      "INSERT INTO url (url, hostname, last_update) values (?, ?, ?)"
    )
    stmt.run(url, hostname, 0)
    return true
  } catch (error) {
    return false
  }
}

export function remove(url: string): void {
  db.prepare("delete from url where url = ?").run(url)
}
