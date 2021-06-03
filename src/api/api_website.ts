import get_db from "./db"
import vm from "vm"
import { ScriptDesc } from "./typing"

const db = get_db()

export function select_all(): ScriptDesc[] {
  const stmt = db.prepare("select * from script")
  const lst: { name: string; re: string }[] = stmt.all()
  return lst.map((obj) => ({
    name: obj.name,
    re: new RegExp(obj.re),
  }))
}
