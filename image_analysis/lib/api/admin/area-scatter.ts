import { ResponseBase } from "@/lib/api"
import { MachinedResultDataObject } from "@/lib/api/request"
import { Prisma } from "@/lib/prisma-client"

export type AreaScatterResultObjectPrisma = Prisma.RequestGetPayload<{
  where: {
    machinedResult: { isNot: null }
  }
  select: {
    createdAt: true
    machinedResult: { select: { data: true } }
  }
}>

export type AreaScatterResultObject = AreaScatterResultObjectPrisma & {
  machinedResult:
    | (NonNullable<AreaScatterResultObjectPrisma["machinedResult"]> & {
        data: MachinedResultDataObject[]
      })
    | null
}

export interface AreaScatter extends ResponseBase {
  data?: AreaScatterResultObject[]
}

export async function areaScatterRequest(): Promise<AreaScatter> {
  const resp = await fetch("/api/admin/area-scatter")

  return await resp.json()
}
