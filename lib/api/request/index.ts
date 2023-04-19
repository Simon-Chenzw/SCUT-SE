import { Prisma } from "@/lib/prisma-client"

export interface MachinedResultDataObject {
  area: string
  score: number
  region: {
    x: number
    y: number
    w: number
    h: number
  }
  message: string
}

export type RequestObjectPrisma = Prisma.RequestGetPayload<{
  include: {
    image: { select: { id: true } }
    machinedResult: true
  }
}>

export type RequestObject = RequestObjectPrisma & {
  machinedResult:
    | (NonNullable<RequestObjectPrisma["machinedResult"]> & {
        data: MachinedResultDataObject[]
      })
    | null
}
