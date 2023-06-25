import Chart, { ReactEChartsProps } from "@/components/chart"
import { RequestObject } from "@/lib/api/request"
import { useMediaQuery } from "@mantine/hooks"
import * as echarts from "echarts"
import { useRouter } from "next/router"

const SVG = "/svg/human_v2.svg"

if (typeof window === "object")
  fetch(SVG)
    .then((resp) => resp.text())
    .then((svg) => echarts.registerMap("organ_diagram", { svg: svg }))

export default function OrganDiagram(props: {
  machinedResult: NonNullable<RequestObject["machinedResult"]>
  style?: ReactEChartsProps["style"]
}) {
  const router = useRouter()
  const isMobile = useMediaQuery("(max-width: 50em)")

  const onEchartReady = (echart: echarts.EChartsType) => {
    echart.on("mouseover", { seriesIndex: 0 }, function (event) {
      echart.dispatchAction({
        type: "highlight",
        geoIndex: 0,
        name: event.name,
      })
    })
    echart.on("mouseout", { seriesIndex: 0 }, function (event) {
      echart.dispatchAction({
        type: "downplay",
        geoIndex: 0,
        name: event.name,
      })
    })
  }

  return (
    <Chart
      onEchartReady={onEchartReady}
      initopts={{
        locale: router.locale?.toLowerCase().startsWith("zh") ? "ZH" : "EN",
        renderer: "svg",
      }}
      option={{
        tooltip: {},
        geo: {
          map: "organ_diagram",
          left: 0,
          right: "60%",
          zoom: isMobile ? 0.75 : 0.5,
          blur: {},
          selectedMode: "single",
          emphasis: {
            // eslint-disable-next-line @typescript-eslint/ban-ts-comment
            /// @ts-ignore
            focus: "self",
            itemStyle: {
              color: null,
            },
            label: {
              position: "bottom",
              distance: 0,
              textBorderColor: "#fff",
              textBorderWidth: 2,
            },
          },
          select: {
            itemStyle: {
              color: "#b50205",
            },
            label: {
              show: false,
              textBorderColor: "#fff",
              textBorderWidth: 2,
            },
          },
        },
        grid: {
          left: "50%",
          top: "10%",
          bottom: "10%",
        },
        xAxis: { data: props.machinedResult.data.map((item) => item.area) },
        yAxis: {},
        series: [
          {
            type: "bar",
            emphasis: {
              focus: "self",
            },
            data: props.machinedResult.data.map((item) => item.score),
          },
        ],
      }}
      settings={{
        notMerge: true,
      }}
      style={props.style}
    />
  )
}
