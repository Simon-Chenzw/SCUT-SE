/* global axios :readonly */

const re = new RegExp("https://qieman.com/portfolios/([^?/]+)")

// Sorry, but because of qieman's anti-crawler measures,
// `x-sign` needs to be updated every day
// Tutorial and the end of this code
const x_sign = "16234792881220C4FEE7E10B172EEFE3EDC6A3CC79B5C"

async function get(url) {
  const tag = re.exec(url)[1]

  const resp = await axios.get(
    `https://qieman.com/pmdj/v1/pomodels/${tag}/nav-history`,
    { headers: { "x-sign": x_sign } }
  )

  if (resp.data === "") throw "爬虫需要更新 x-sign"

  return resp.data.map((ele) => ({
    date: ele.navDate,
    value: ele.nav,
  }))
}

/**
 * Tutorial of getting x-sign:
 * 1. use chrome open one of qieman's fund page
 * 2. press F12 open DevTool & choice 'Network' tab
 * 3. press Ctrl+R & use Filter to search 'nav-history'
 * 4. choice nav-history record & find x-sign from 'Request Headers'
 */
