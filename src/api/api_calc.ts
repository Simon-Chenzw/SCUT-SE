import type { FundInfo } from "./typing"

interface FundCalc {
  avg: number
  mdd: number //最大回撤，风险越小越好
  roi: number //年化收益率，增长越快越好
  sharpeRatio: number //夏普率
  annualizedVolatility: number //年化波动率，越小越好
}

//只算起始点投出和结束点收入的年化波动率
function xirr_sin(fund: FundInfo): number {
  const arr_length = fund.length - 1
  const years =
    (fund[arr_length].date - fund[0].date) / (1000 * 60 * 60 * 24 * 365)
  let residual = 1.0
  let step = 0.05
  let guess = 0.05
  const epsilon = 0.0001
  let limit = 10000
  while (Math.abs(residual) > epsilon && limit > 0) {
    limit--
    residual = 0.0
    residual += -fund[0].value
    residual += fund[arr_length].value / Math.pow(guess, years)
    if (Math.abs(residual) > epsilon) {
      if (residual > 0) {
        guess += step
      } else {
        guess -= step
        step /= 2.0
      }
    }
  }
  return Number((guess - 1).toFixed(4))
}

//计算最大回撤
function cal_MDD(fund: FundInfo): number {
  let max_MDD = 0,
    temp_MDD = 0,
    max_value = 0
  for (let i = 0; i < fund.length; i++) {
    max_value = Math.max(max_value, fund[i].value)
    temp_MDD = 1 - fund[i].value / max_value
    max_MDD = Math.max(temp_MDD, max_MDD)
  }
  max_MDD = Number(max_MDD.toFixed(4))
  return max_MDD
}

//年化收益率
function cal_roi(fund: FundInfo): number {
  return xirr_sin(fund)
}

//取无风险收益率为0.03
function cal_sharpeRation(fund: FundInfo, annV: number) {
  const inital_value = fund[0].value
  const arr_length = fund.length - 1
  const final_value = fund[arr_length].value
  const sharpeRation = Number(
    ((final_value - inital_value - 0.03) / annV).toFixed(2)
  )
  return sharpeRation
}

//计算年化波动率，使用回望波动率计算
function cal_annualizedVolatility(fund: FundInfo) {
  let sum = 0,
    sum_square = 0
  const len = fund.length
  const lg_arr = []
  for (let i = 0; i < len - 1; ++i) {
    lg_arr[i] = Math.log(fund[i + 1].value / fund[i].value)
    sum += lg_arr[i]
    sum_square += lg_arr[i] * lg_arr[i]
  }

  const dev = Math.sqrt(
    sum_square / (len - 2) - (sum * sum) / ((len - 1) * (len - 2))
  )
  const annualizedVolatility = Number((dev * Math.sqrt(250)).toFixed(4))
  if (annualizedVolatility > 0.3) {
    return cal_v2(fund)
  }
  return annualizedVolatility
}

//使用日净值计算波动率
function cal_v2(fund: FundInfo) {
  let sum = 0,
    sum_square = 0
  const len = fund.length
  let temp
  for (let i = 0; i < len - 1; ++i) {
    let diffday = (fund[i + 1].date - fund[i].date) / (1000 * 60 * 60 * 24)
    if (diffday < 5) {
      diffday = 1
    }
    temp = (fund[i + 1].value - fund[i].value) / (fund[i].value * diffday)
    sum += temp
    sum_square += temp * temp
  }
  const dev = Math.sqrt(
    sum_square / (len - 2) - (sum * sum) / ((len - 1) * (len - 2))
  )
  const annualizedVolatility = Number((dev * Math.sqrt(250)).toFixed(4))
  return annualizedVolatility
}

export function calc(fund: FundInfo): FundCalc {
  let sum = 0
  for (const ele of fund) sum += ele.value
  let MDD = cal_MDD(fund)
  let roi = cal_roi(fund)
  let annualizedVolatility = cal_annualizedVolatility(fund)
  const sharpeRatio = cal_sharpeRation(fund, annualizedVolatility)
  annualizedVolatility = Number((annualizedVolatility * 100).toFixed(2))
  MDD = Number((MDD * 100).toFixed(2))
  roi = Number((roi * 100).toFixed(2))

  return {
    // Percentage
    avg: sum / fund.length,
    mdd: MDD,
    roi: roi,
    sharpeRatio: sharpeRatio,
    annualizedVolatility: annualizedVolatility,
  }
}
