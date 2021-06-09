import db from "./db"
import { WebsiteDesc } from "./typing"

export function select_all(): WebsiteDesc[] {
  return db.prepare("select * from website").all()
}

export function select_host(hostname: string): string | undefined {
  const stmt = db.prepare("select name from website where hostname = ?")
  return stmt.get(hostname).name
}

export function insert(desc: WebsiteDesc): boolean {
  try {
    const stmt = db.prepare("insert into website (name, hostname) values (?,?)")
    stmt.run(desc.name, desc.hostname)
    return true
  } catch (error) {
    return false
  }
}

export function update(name: string, desc: WebsiteDesc): void {
  const stmt = db.prepare(
    "update website set name = ?, hostname = ? where name = ?"
  )
  stmt.run(desc.name, desc.hostname, name)
}

export function remove(name: string): void {
  db.prepare("delete from website where name = ?").run(name)
}

export function get_script(hostname: string): string | undefined {
  return db
    .prepare("select script from website where hostname = ?")
    .get(hostname).script
}
