// database script
export interface ScriptDesc {
  readonly name: string // website name, like danjuan or qieman. file: ${name}.js
  readonly re: RegExp // RegExp of url
}

// database url
export interface URLDesc {
  readonly url: string
  readonly name: string // from script.name
  readonly tag: string // fund tag in current website
}

// database fund
export interface DailyInfo {
  readonly date: Date // YYYY-MM-DD
  readonly value: number // fund value
}

export type FundInfo = DailyInfo[]
