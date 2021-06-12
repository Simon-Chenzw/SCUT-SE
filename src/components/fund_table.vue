<template>
  <div>
    <v-row>
      <v-col cols="12" sm="6" md="5">
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
              label="开始日期"
              prepend-icon="mdi-calendar"
              readonly
              v-bind="attrs"
              v-on="on"
            ></v-text-field>
          </template>
          <v-date-picker
            v-model="start_date"
            @input="menu1 = false"
            @change="update()"
          ></v-date-picker>
        </v-menu>
      </v-col>

      <v-spacer></v-spacer>

      <v-col cols="12" sm="6" md="5">
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
              label="结束日期"
              prepend-icon="mdi-calendar"
              readonly
              v-bind="attrs"
              v-on="on"
            ></v-text-field>
          </template>
          <v-date-picker
            v-model="end_date"
            @input="menu2 = false"
            @change="update()"
          ></v-date-picker>
        </v-menu>
      </v-col>

      <v-spacer></v-spacer>

      <v-col cols="12" sm="6" md="2">
        <div class="cent">
          <v-icon x-large @click="reset()"> mdi-backup-restore </v-icon>
        </div>
      </v-col>
    </v-row>

    <highcharts :options="chartOptions"> </highcharts>

    <template>
      <v-data-table
        dense
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
import highcharts, { chart, each } from "highcharts"
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
    start_date: "2000-01-01",
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
            ? "鼠标拖动可以进行缩放，点击下方圆点可隐藏对应股票曲线"
            : "手势操作进行缩放，点击下方圆点可隐藏对应股票曲线",
      },
      xAxis: {
        title: {
          text: "日期",
        },
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
          text: "净值",
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
        marker: {
          enabled: false,
          //radius: 10
        },
      },

      series: [] as any,
    },
    headers: [
      {
        text: "基金编码",
        align: "start",
        sortable: false,
        value: "name",
      },
      { text: "年化收益率 (%)", value: "Increase" },
      { text: "最大回撤 (%)", value: "Drawdown" },
      { text: "夏普率", value: "Sharpe_Ratio" },
      { text: "年化波动率 (%)", value: "Volatility" },
    ],
    desserts: [] as any,
    min_unix_date: 946656000000,
    max_unix_date: 4102416000000,
    min_date: "1970-01-01",
    max_date: "1970-01-01",
  }),
  methods: {
    test() {
      this.get_all_data()
    },
    reset() {
      this.min_unix_date = 946656000000
      this.max_unix_date = 4102416000000
      this.start_date = "2000-01-01"
      this.end_date = this.date
      this.init()
    },
    update() {
      const start_unix_time = new Date(this.start_date + " 00:00:00:000")
      const end_unix_time = new Date(this.end_date + " 00:00:00:000")
      if (start_unix_time.getTime() > end_unix_time.getTime()) {
        window.alert("start time cann't large than end time!")
        return
      }
      this.min_unix_date = start_unix_time.getTime()
      this.max_unix_date = end_unix_time.getTime()
      this.get_all_data()
    },
    get_all_url: async function () {
      this.url = api_url.select_all()
    },
    get_all_data: async function () {
      // @ts-ignore
      var change_data = new Array()
      // @ts-ignore
      var change_total = new Array()
      const min_unix_date = this.min_unix_date
      const max_unix_date = this.max_unix_date

      this.url.forEach(function (this_url) {
        const basic_data = api_fund.select(this_url.url)
        if (basic_data.length === 0) return
        var decode_data = new Array()
        let calc_data: FundInfo = []
        var basic_line: number = 0
        basic_data.sort(function (x, y) {
          return x.date - y.date
        })

        basic_data.forEach(function (each_data) {
          if (
            each_data.date >= min_unix_date &&
            each_data.date <= max_unix_date
          ) {
            if (basic_line === 0) basic_line = each_data.value
            calc_data.push({
              date: each_data.date,
              value: each_data.value / basic_line,
            })
            decode_data.push([each_data.date, each_data.value / basic_line])
          }
        })
        if (calc_data.length === 0) return

        calc_data.sort(function (x, y) {
          return x.date - y.date
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
.cent {
  height: 60px;
  margin: 0;
  display: flex;
  justify-content: center;
  align-items: center;
}
</style>
