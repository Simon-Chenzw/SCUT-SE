<template>
  <div>
    <v-row>
      <v-col cols="12" sm="6">
        <v-date-picker v-model="dates" range></v-date-picker>
      </v-col>
      <v-col cols="12" sm="6">
        <v-text-field
          v-model="dateRangeText"
          label="Date range"
          prepend-icon="mdi-calendar"
          readonly
        ></v-text-field>
        <v-btn @click="test()"> change </v-btn>
      </v-col>
    </v-row>
    <highcharts :options="chartOptions"> </highcharts>

    <v-btn @click="test()">Change</v-btn>
    <template>
      <v-data-table
        :headers="headers"
        :items="desserts"
        :sort-desc="[false, true]"
        multi-sort
        class="elevation-1"
      ></v-data-table>
    </template>
  </div>
</template>
<script lang="ts">
import Vue from "vue"
import highcharts from "highcharts"
import HighchartsVue from "highcharts-vue"
import type * as Tapi_website from "../api/api_website"
import type * as Tapi_url from "../api/api_url"
import type * as Tapi_fund from "../api/api_fund"
import type * as Tapi_calc from "../api/api_calc"
import type { URLDesc, FundInfo } from "../api/typing"

declare const api_website: typeof Tapi_website
declare const api_url: typeof Tapi_url
declare const api_fund: typeof Tapi_fund
declare const api_calc: typeof Tapi_calc

interface DataDesc {
  name?: string
  data?: []
}

interface FundCalc {
  avg: number
  mdd: number //最大回撤，风险越小越好
  roi: number //年化收益率，增长越快越好
  sharpeRatio: number //夏普率，越小越好
  annualizedVolatility: number //年化波动率，越小越好
}

Vue.use(HighchartsVue)
export default Vue.extend({
  name: "fund",
  mounted() {
    this.init()
  },
  data: () => ({
    url: [] as URLDesc[],
    dates: ["2019-09-10", "2019-09-20"],
    chartOptions: {
      chart: {
        zoomType: "x",
      },
      title: {
        text: "收益率曲线",
      },
      subtitle: {
        text:
          document.ontouchstart === undefined
            ? "鼠标拖动可以进行缩放"
            : "手势操作进行缩放",
      },
      xAxis: {
        type: "datetime",
        dateTimeLabelFormats: {
          millisecond: "%H:%M:%S.%L",
          second: "%H:%M:%S",
          minute: "%H:%M",
          hour: "%H:%M",
          day: "%m-%d",
          week: "%m-%d",
          month: "%Y-%m",
          year: "%Y",
        },
      },
      tooltip: {
        dateTimeLabelFormats: {
          millisecond: "%H:%M:%S.%L",
          second: "%H:%M:%S",
          minute: "%H:%M",
          hour: "%H:%M",
          day: "%Y-%m-%d",
          week: "%m-%d",
          month: "%Y-%m",
          year: "%Y",
        },
      },
      yAxis: {
        title: {
          text: "ytitle",
        },
      },
      plotOptions: {
        area: {
          marker: {
            radius: 2,
            lineWidth: 1,
            states: {
              hover: {
                lineWidth: 1,
              },
            },
            threshold: null,
          },
        },
      },
      series: [] as any,
    },
    headers: [
      {
        text: "Name",
        align: "start",
        sortable: false,
        value: "name",
      },
      { text: "Increase", value: "Increase" },
      { text: "Drawdown", value: "Drawdown" },
      { text: "Sharpe Ratio", value: "Sharpe_Ratio" },
      { text: "Volatility", value: "Volatility" },
    ],
    desserts: [] as any,
  }),
  methods: {
    test() {
      this.get_all_data()
    },
    get_all_url: async function () {
      this.url = api_url.select_all()
    },
    get_all_data: async function () {
      var change_data = new Array()
      var change_total = new Array()
      this.url.forEach(function (this_url) {
        const basic_data = api_fund.select(this_url.url)
        var decode_data = new Array()
        let calc_data: FundInfo = []
        basic_data.forEach(function (each_data) {
          calc_data.push({ date: each_data.date, value: each_data.value })
          decode_data.push([each_data.date, each_data.value])
        })
        const tmp: FundCalc = api_calc.calc(calc_data)
        change_total.push({
          name: this_url.url.split("/").slice(-1),
          Increase: tmp.roi,
          Drawdown: tmp.mdd,
          Sharpe_Ratio: tmp.sharpeRatio,
          Volatility: tmp.annualizedVolatility,
        })
        change_data.push({
          name: this_url.url.split("/").slice(-1),
          data: decode_data,
        })
      })
      // console.log(change_data)
      this.desserts = change_total
      this.chartOptions.series = change_data
    },
    init: async function () {
      await this.get_all_url()
      await this.get_all_data()
    },
  },
  computed: {
    dateRangeText() {
      return this.dates.join("~")
    },
  },
})
</script>

<style>
.highcharts-container {
  width: 600px;
  height: 400px;
  border: 1px solid #ddd;
  margin: auto;
}
</style>
