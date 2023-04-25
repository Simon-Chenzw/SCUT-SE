import { PrismaClient } from "../lib/prisma-client/index.js"

const prisma = new PrismaClient({ log: ["query"] })

export async function create_user(
  number = 10000,
  createStart = new Date("2023-01-01"),
  createEnd = new Date("2023-04-30")
) {
  /** @type {Date[]} */
  const dates = []
  while (dates.length < number) {
    const n = Math.trunc(Math.random() * 100)
    const ctr =
      createStart.getTime() +
      Math.random() * (createEnd.getTime() - createStart.getTime())
    for (let i = 0; i < n - 1 && dates.length < number; i++)
      dates.push(new Date(ctr + 3600 * (Math.random() - 0.5)))
  }

  const task = new Array(number)
    .fill(0)
    .map((v, idx) => ({
      idx: idx,
      name: `User${idx + 1}`,
      email: `User${idx + 1}@local`,
      createdAt: dates[idx],
    }))
    .map(({ name, email, createdAt }) =>
      prisma.user.upsert({
        where: { email },
        create: { name, email, createdAt },
        update: { createdAt },
      })
    )

  await Promise.all(task)
}

async function main() {
  await create_user()
  console.log(await prisma.user.count())
}

main()
