import db from "./db"
import { URLDesc } from "./typing"

export function select_all(): URLDesc[] {
  return db.prepare("select * from url").all()
}
