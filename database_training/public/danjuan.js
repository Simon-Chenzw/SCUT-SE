/* global axios :readonly */

const re = new RegExp("danjuanapp.com/strategy/([^?/]+)")

async function get(url) {
  const tag = re.exec(url)[1]

  const resp = await axios.get(
    `https://danjuanapp.com/djapi/plan/v2/growth/${tag}?type=2&day=all`
  )

  return resp.data.data.fund_nav_growth.map((ele) => ({
    date: new Date(ele.date).valueOf(),
    value: Number(ele.value) + 1,
  }))
}
