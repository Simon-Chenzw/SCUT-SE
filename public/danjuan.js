// eslint-disable-next-line @typescript-eslint/no-var-requires
/* global axios :readonly */

const re = new RegExp("danjuanapp.com/strategy/([^?/]+)")

// eslint-disable-next-line @typescript-eslint/no-unused-vars
async function get(url) {
  const tag = re.exec(url)[1]

  const resp = await axios.get(
    `https://danjuanapp.com/djapi/plan/v2/growth/${tag}?type=2&day=all`
  )

  const lst = resp.data.data.fund_nav_growth

  return lst.map((ele) => ({
    date: new Date(ele.date).valueOf(),
    value: Number(ele.value),
  }))
}