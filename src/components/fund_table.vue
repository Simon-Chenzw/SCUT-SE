<template>
  <div>
    <v-row>
      <v-col cols="12" sm="6" md="4">
        <v-menu
          v-model="menu1"
          :close-on-content-click="false"
          absolute
          :nudge-right="40"
          transition="scale-transition"
          offset-y
          min-width="auto"
        >
          <template v-slot:activator="{ on, attrs }">
            <v-text-field
              v-model="start_date"
              label="Start date"
              prepend-icon="mdi-calendar"
              readonly
              v-bind="attrs"
              v-on="on"
            ></v-text-field>
          </template>
          <v-date-picker
            v-model="start_date"
            @input="menu1 = false"
          ></v-date-picker>
        </v-menu>
      </v-col>

      <v-spacer></v-spacer>

      <v-col cols="12" sm="6" md="4">
        <v-menu
          v-model="menu2"
          :close-on-content-click="false"
          absolute
          :nudge-right="40"
          transition="scale-transition"
          offset-y
          min-width="auto"
        >
          <template v-slot:activator="{ on, attrs }">
            <v-text-field
              v-model="end_date"
              label="End date"
              prepend-icon="mdi-calendar"
              readonly
              v-bind="attrs"
              v-on="on"
            ></v-text-field>
          </template>
          <v-date-picker
            v-model="end_date"
            @input="menu2 = false"
          ></v-date-picker>
        </v-menu>
      </v-col>

      <v-spacer></v-spacer>

      <v-col cols="12" sm="6" md="2">
        <v-btn @click="update()">UPDATE</v-btn>
      </v-col>

      <v-spacer></v-spacer>

      <v-col cols="12" sm="6" md="2">
        <v-btn @click="reset()">RESET</v-btn>
      </v-col>
    </v-row>

    <highcharts :options="chartOptions"> </highcharts>

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
import highcharts, { each } from "highcharts"
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
    date: new Date().toISOString().substr(0, 10),
    start_date: new Date().toISOString().substr(0, 10),
    end_date: new Date().toISOString().substr(0, 10),
    menu1: false,
    menu2: false,
    url: [] as URLDesc[],
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
    min_unix_date: 946656000000,
    max_unix_date: 4102416000000,
    min_date: "1970-01-01",
    max_date: "1970-01-01",
  }),
  methods: {
    test() {
      console.log("test")
    },
    reset() {
      this.min_unix_date = 946656000000
      this.max_unix_date = 4102416000000
      this.init()
    },
    update() {
      const start_unix_time = new Date(this.start_date + " 00:00:00:000")
      const end_unix_time = new Date(this.end_date + " 00:00:00:000")
      if (start_unix_time.getTime() > end_unix_time.getTime()) {
        window.alert("start time can't large than end time!")
        return
      }
      this.min_unix_date = start_unix_time.getTime()
      this.max_unix_date = end_unix_time.getTime()
      this.init()
    },
    get_all_url: async function () {
      this.url = api_url.select_all()
    },
    get_all_data: async function () {
      var change_data = new Array()
      var change_total = new Array()
      const min_unix_date = this.min_unix_date
      const max_unix_date = this.max_unix_date
      this.url.forEach(function (this_url) {
        const basic_data = api_fund.select(this_url.url)
        const p = this_url.url.search("danjuan") == -1
        var decode_data = new Array()
        let calc_data: FundInfo = []
        basic_data.forEach(function (each_data) {
          if (
            each_data.date >= min_unix_date &&
            each_data.date <= max_unix_date
          ) {
            calc_data.push({
              date: each_data.date,
              value: p ? each_data.value : each_data.value + 1,
            })
            decode_data.push([
              each_data.date,
              p ? each_data.value : each_data.value + 1,
            ])
          }
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
    unix_to_date(date: Date) {
      const Y = date.getFullYear() + "-"
      const M =
        (date.getMonth() + 1 < 10
          ? "0" + (date.getMonth() + 1)
          : date.getMonth() + 1) + "-"
      const D = date.getDate()
      return Y + M + D
    },
    init: async function () {
      await this.get_all_url()
      await this.get_all_data()
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
