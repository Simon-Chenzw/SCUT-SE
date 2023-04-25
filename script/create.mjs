import { PrismaClient } from "../lib/prisma-client/index.js"

const prisma = new PrismaClient({ log: ["query"] })

/**
 * @param {number} val
 * @param {number} min
 * @param {number} max
 * @returns {number}
 */
const clamp = (val, min, max) => (val > max ? max : val < min ? min : val)

// return (0, 1)
const randOpen = () => {
  let r = 0
  while (r === 0) r = Math.random()
  return r
}

const gaussian = () =>
  Math.sqrt(-2 * Math.log(randOpen())) * Math.cos(2 * Math.PI * randOpen())

/**
 * @param {[number, number][]} p
 * @returns {(x:number)=>number}
 */
const lagrange = (p) => (x) =>
  p.reduce(
    (acc, [xi, yi], i) =>
      acc +
      (yi * p.reduce((acc, [xj], j) => (i !== j ? acc * (x - xj) : acc), 1)) /
        p.reduce((acc, [xj], j) => (i !== j ? acc * (xi - xj) : acc), 1),
    0
  )

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

export async function create_result(
  number = 1000,
  createStart = new Date("2023-01-01"),
  createEnd = new Date("2023-04-30"),
  email = "User1@local"
) {
  await prisma.user.findUniqueOrThrow({ where: { email } })
  await prisma.machinedResult.deleteMany({
    where: { request: { user: { email } } },
  })
  await prisma.request.deleteMany({ where: { user: { email } } })

  const getDate = (x) =>
    new Date(createStart.getTime() * (1 - x) + createEnd.getTime() * x)

  const basicGet =
    (area, ...args) =>
    (x) => ({
      area,
      score: clamp(
        lagrange(args.map((v, i) => [i / (args.length - 1), v]))(x) +
          gaussian() * 5,
        0,
        100
      ),
      region: { h: 0, w: 0, x: 0, y: 0 },
      message: "",
    })
  const getHead = basicGet("head", 40, 55, 50, 40)
  const getBody = basicGet("body", 50, 30, 60, 65)
  const getLeg = basicGet("leg", 70, 35, 40, 50)

  const task = new Array(number)
    .fill(0)
    .map((v, idx) => idx / number)
    .map((x) =>
      prisma.request.create({
        data: {
          createdAt: getDate(x),
          user: { connect: { email } },
          machinedResult: {
            create: {
              createdAt: getDate(x),
              data: [getHead(x), getBody(x), getLeg(x)],
            },
          },
        },
      })
    )

  await Promise.all(task)
}

async function main() {
  // await create_user()
  // console.log(await prisma.user.count())
  await create_result()
  console.log(await prisma.request.count())
  console.log(await prisma.machinedResult.count())
}

main()
