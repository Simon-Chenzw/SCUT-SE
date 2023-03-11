import jwt from "jsonwebtoken"

const PUBLIC_KEY = process.env.PUBLIC_KEY || ""
const PRIVATE_KEY = process.env.PRIVATE_KEY || ""
const JWT_SIGNING_ALGORITHMS = "RS512"

export default class Token {
  static EXP = 30 * 24 * 60 * 60 // 30 days

  constructor(public id: string) {}

  to_jwt(): string {
    return jwt.sign({ id: this.id }, PRIVATE_KEY, {
      algorithm: JWT_SIGNING_ALGORITHMS,
      expiresIn: Token.EXP,
    })
  }

  static from_jwt(token: string): Token | null {
    try {
      const payload = jwt.verify(token, PUBLIC_KEY, {
        algorithms: [JWT_SIGNING_ALGORITHMS],
      })
      if (typeof payload === "string") return null
      else return new Token(payload.id)
    } catch {
      return null
    }
  }
}
