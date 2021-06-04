import db from "./db"
import { ScriptDesc } from "./typing"

export function select_all(): ScriptDesc[] {
  return db.prepare("select * from script").all()
}

export function insert(script: ScriptDesc): boolean {
  try {
    const stmt = db.prepare("insert into script values (?,?)")
    stmt.run(script.name, script.hostname)
    return true
  } catch (error) {
    return false
  }
}

export function update(name: string, desc: ScriptDesc): void {
  const stmt = db.prepare("update name = ?, hostname = ? where name = ?")
  stmt.run(name, desc.name, desc.hostname)
}

export function remove(name: string): void {
  const stmt = db.prepare("delete from script where name = ?")
  stmt.run(name)
}
