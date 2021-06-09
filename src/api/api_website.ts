import db from "./db"
import { WebsiteDesc } from "./typing"

export function select_all(): WebsiteDesc[] {
  return db.prepare("select * from website").all()
}

export function select_host(hostname: string): string | undefined {
  const stmt = db.prepare("select name from website where hostname = ?")
  return stmt.get(hostname).name
}

export function insert(script: WebsiteDesc): boolean {
  try {
    const stmt = db.prepare("insert into script (name, hostname) values (?,?)")
    stmt.run(script.name, script.hostname)
    return true
  } catch (error) {
    return false
  }
}

export function update(name: string, desc: WebsiteDesc): void {
  const stmt = db.prepare("update name = ?, hostname = ? where name = ?")
  stmt.run(name, desc.name, desc.hostname)
}

export function remove(name: string): void {
  db.prepare("delete from website where name = ?").run(name)
}
