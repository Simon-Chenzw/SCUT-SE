
import type { FundInfo } from "./typing"



interface FundCalc {
    avg: number
    mdd: number //最大回撤，风险越小越好
    roi: number //年化收益率，增长越快越好
    sharpeRatio: number //夏普率，越小越好
    annualizedVolatility: number //年化波动率，越小越好
}
function cal_MDD(fund: FundInfo): number {
    let max_MDD = 0,
        temp_MDD = 0,
        max_value = 0
    for (let i = 0; i < fund.length; i++) {
        max_value = Math.max(max_value, fund[i].value)
        temp_MDD = 1 - (fund[i].value + 1) / (max_value + 1)
        max_MDD = Math.max(temp_MDD, max_MDD)
    }
    return max_MDD
}
//年化收益率
function cal_roi(fund: FundInfo): number {
    const inital_value = fund[0].value
    const arr_length = fund.length - 1
    const final_value = fund[arr_length].value
    const diff =
        (fund[arr_length].date - fund[0].date) /
        (24 * 3600 * 1000)

    return ((final_value - inital_value) * 365) / diff
}

//取无风险收益率为0.03
function cal_sharpeRation(fund: FundInfo, annV: number) {
    const inital_value = fund[0].value
    const arr_length = fund.length - 1
    const final_value = fund[arr_length].value
    return (final_value - inital_value - 0.03) / annV
}

function cal_annualizedVolatility(fund: FundInfo) {
    let sum = 0,
        sum_square = 0
    const len = fund.length
    const lg_arr = []
    for (let i = 0; i < len - 1; ++i) {
        lg_arr[i] = Math.log((fund[i + 1].value + 1) / (fund[i].value + 1))
        sum += lg_arr[i]
        sum_square += lg_arr[i] * lg_arr[i]
    }
    const dev = Math.sqrt(
        sum_square / (len - 2) - (sum * sum) / ((len - 1) * (len - 2))
    )
    return dev * Math.sqrt(250)
}

export function calc(fund: FundInfo): FundCalc {
    let sum = 0
    for (const ele of fund) sum += ele.value
    const MDD = cal_MDD(fund)
    const roi = cal_roi(fund)
    const annualizedVolatility = cal_annualizedVolatility(fund)
    const sharpeRatio = cal_sharpeRation(fund, annualizedVolatility)
    return {
        avg: sum / fund.length,
        mdd: MDD,
        roi: roi,
        sharpeRatio: sharpeRatio,
        annualizedVolatility: annualizedVolatility,
    }
}

