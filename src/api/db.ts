import sqlite3 from "better-sqlite3"
import fs from "fs"
import path from "path"

declare const __static: string

export function get_db(): sqlite3.Database {
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
    const sql_path = path.join(__static, "create.sql")
    db.exec(fs.readFileSync(sql_path, "utf8"))
    console.log("rebuild successful")
  }
  db.pragma("foreign_keys = ON")
  return db
}

const db = get_db()
export default db
