// database script
export interface ScriptDesc {
  readonly name: string // website name, like danjuan or qieman. file: ${name}.js
  readonly hostname: string // hostname of website
}

// database url
export interface URLDesc {
  readonly url: string
  readonly name: string // from script.name
  readonly last_update: number // fund tag in current website
}

// database fund
export interface DailyInfo {
  readonly date: number // timestamp
  readonly value: number // fund value
}

export type FundInfo = DailyInfo[]
