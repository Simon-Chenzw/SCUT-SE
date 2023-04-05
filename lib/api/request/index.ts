import { Prisma } from "@/lib/prisma-client"

export type RequestObject = Prisma.RequestGetPayload<{
  include: {
    image: { select: { id: true } }
    machinedResult: true
  }
}>
