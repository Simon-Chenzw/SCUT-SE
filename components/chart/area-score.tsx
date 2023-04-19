import Chart, { ReactEChartsProps } from "@/components/chart"
import { MachinedResultObject, RequestObject } from "@/lib/api/request"
import { requestListRequest } from "@/lib/api/request/list"
import { useRouter } from "next/router"
import { useEffect, useState } from "react"

export default function AreaScoreChart(props: {
  style?: ReactEChartsProps["style"]
}) {
  const router = useRouter()
  const [requests, setRequests] = useState<RequestObject[]>()
  const [chartData, setChartData] =
    useState<ReactEChartsProps["option"]["series"]>()

  useEffect(() => {
    ;(async () => {
      const resp = await requestListRequest({})
      if (resp.data) setRequests(resp.data.requests)
    })()
  }, [])

  useEffect(() => {
    if (requests === undefined) {
      setChartData(undefined)
      return
    }

    type Serier = Exclude<typeof chartData, unknown[]> & {
      type: "line"
      data: [Date, number][]
    }
    type RequestObjectWithNonNull = RequestObject & {
      machinedResult: NonNullable<RequestObject["machinedResult"]>
    }

    const data = requests
      .filter((v): v is RequestObjectWithNonNull => v.machinedResult !== null)
      .flatMap((v) =>
        (v.machinedResult.data as unknown as MachinedResultObject[]).map(
          (vv) => [vv.area, new Date(v.createdAt), vv.score] as const
        )
      )
      .reduce((data: Record<string, Serier>, [area, date, score]) => {
        data[area] ??= { name: area, type: "line", data: [] }
        data[area].data.push([date, score])
        return data
      }, {})

    setChartData(Object.values(data))
  }, [requests])

  return (
    <Chart
      loading={requests === undefined}
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
        series: chartData,
      }}
      settings={{
        notMerge: true,
      }}
      style={props.style}
    />
  )
}
