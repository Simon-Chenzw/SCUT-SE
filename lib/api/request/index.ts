import { Prisma } from "@/lib/prisma-client"

export interface MachinedResultObject {
  area: string
  region: {
    x: number
    y: number
    w: number
    h: number
  }
  message: string
}

export type RequestObject = Prisma.RequestGetPayload<{
  include: {
    image: { select: { id: true } }
    machinedResult: true
  }
}>
