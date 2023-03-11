import { NextApiRequest, NextApiResponse } from "next"

export interface ResponseBase {
  code: number
  message: string
}

export interface JsonApiRequest<T = never>
  extends Omit<NextApiRequest, "body"> {
  body: T
}

export type JsonApiResponse<T extends ResponseBase> = NextApiResponse<T>
