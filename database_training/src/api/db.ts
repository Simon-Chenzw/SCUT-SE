import sqlite3 from "better-sqlite3"
import fs from "fs"
import path from "path"

declare const __static: string

function init_db(db: sqlite3.Database): void {
  db.exec(fs.readFileSync(path.join(__static, "create.sql"), "utf8"))
  const danjuan_code = fs.readFileSync(
    path.join(__static, "danjuan.js"),
    "utf8"
  )
  db.prepare("update website set script = ? where hostname = ?").run(
    danjuan_code,
    "danjuanapp.com"
  )
  const qieman_code = fs.readFileSync(path.join(__static, "qieman.js"), "utf8")
  db.prepare("update website set script = ? where hostname = ?").run(
    qieman_code,
    "qieman.com"
  )
}

export function get_db(): sqlite3.Database {
  // if (process.env.NODE_ENV !== "production") fs.rmSync("fund_data.sqlite3")
  let db = undefined
  const config = {
    verbose: console.debug,
  }
  try {
    db = new sqlite3("fund_data.sqlite3", { fileMustExist: true, ...config })
    console.log("Database exists.")
  } catch (error) {
    console.log("Database doesn't exist, rebuilding...")
    db = new sqlite3("fund_data.sqlite3", config)
    init_db(db)
    console.log("rebuild successful")
  }
  db.pragma("foreign_keys = ON")
  return db
}

const db = get_db()
export default db
