import { PrismaClient } from "@/lib/prisma-client"

const globalForPrisma = global as unknown as { prisma: PrismaClient }

let prisma: PrismaClient

if (process.env.NODE_ENV === "production") {
  prisma = new PrismaClient({ log: ["query"] })
} else {
  if (!globalForPrisma.prisma) {
    globalForPrisma.prisma = new PrismaClient({ log: ["query"] })
  }
  prisma = globalForPrisma.prisma
}

export default prisma
