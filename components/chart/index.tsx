import { EChartsOption, getInstanceByDom, init, SetOptionOpts } from "echarts"
import React, { CSSProperties, useEffect, useRef } from "react"

type EChartsInitOpts = Parameters<typeof init>[2]

export interface ReactEChartsProps {
  // Echarts
  theme?: "light" | "dark"
  initopts?: EChartsInitOpts
  option: EChartsOption
  settings?: SetOptionOpts
  loading?: boolean
  // Html
  style?: CSSProperties
}

export default function Chart({
  theme,
  initopts,
  option,
  settings,
  loading,
  style,
}: ReactEChartsProps): JSX.Element {
  const chartRef = useRef<HTMLDivElement>(null)

  // init & theme
  useEffect(() => {
    const ref = chartRef.current
    if (ref === null) return
    const chart = init(ref, theme, initopts)

    const resizeChart = () => chart.resize()
    window.addEventListener("resize", resizeChart)

    return () => {
      chart.dispose()
      window.removeEventListener("resize", resizeChart)
    }
  }, [theme, initopts])

  // option & settings
  useEffect(() => {
    const ref = chartRef.current
    if (ref === null) return
    const chart = getInstanceByDom(ref)
    if (chart === undefined) return
    chart.setOption(option, settings)
  }, [theme, initopts, option, settings])

  // loading
  useEffect(() => {
    const ref = chartRef.current
    if (ref === null) return
    const chart = getInstanceByDom(ref)
    if (chart === undefined) return
    if (loading === true) chart.showLoading()
    else chart.hideLoading()
  }, [theme, initopts, loading])

  return (
    <div
      ref={chartRef}
      style={{ width: "100%", height: "100%", minHeight: "300px", ...style }}
    />
  )
}
