import Chart, { ReactEChartsProps } from "@/components/chart"
import { userCreateAggRequest } from "@/lib/api/admin/user-create-agg"
import { useRouter } from "next/router"
import { useEffect, useState } from "react"

export default function UserCreateAggChart(props: {
  style?: ReactEChartsProps["style"]
}) {
  const router = useRouter()
  const [dates, setDates] = useState<Date[]>()
  const [chartData, setChartData] = useState<[Date, number][]>()

  useEffect(() => {
    ;(async () => {
      const resp = await userCreateAggRequest()
      if (resp.data) setDates(resp.data.map((v) => new Date(v)).sort())
    })()
  }, [])

  useEffect(() => {
    if (dates === undefined || dates.length === 0) {
      setChartData(undefined)
      return
    }

    const data: [Date, number][] = dates.map((v, idx) => [v, idx + 1])
    data.unshift([new Date(data[0][0].getTime() - 24 * 60 * 60 * 1000), 0])
    data.push([
      new Date(data[data.length - 1][0].getTime() + 24 * 60 * 60 * 1000),
      data[data.length - 1][1],
    ])

    setChartData(data)

    console.log(chartData)
  }, [dates])

  return (
    <Chart
      loading={dates === undefined}
      initopts={{
        locale: router.locale?.toLowerCase().startsWith("zh") ? "ZH" : "EN",
        renderer: "svg",
      }}
      option={{
        grid: {
          left: "2%",
          right: "2%",
          bottom: "2%",
          containLabel: true,
        },
        legend: {
          show: true,
          type: "scroll",
          orient: "horizontal",
          top: 10,
          right: 30,
        },
        tooltip: {
          trigger: "axis",
        },
        toolbox: {
          top: 10,
          feature: {
            saveAsImage: {},
          },
        },
        xAxis: { type: "time" },
        yAxis: { type: "value" },
        series: {
          type: "line",
          smooth: true,
          symbol: "none",
          areaStyle: {},
          data: chartData,
        },
      }}
      settings={{
        notMerge: true,
      }}
      style={props.style}
    />
  )
}
