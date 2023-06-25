<template>
  <v-card elevation="2">
    <v-card-title> 上传 excel </v-card-title>
    <v-card-text>
      <v-container>
        格式要求：
        <ol>
          <li>一个文件可以有多个表</li>
          <li>每个表的第一行为字段名称</li>
          <li>接下来每一行为一个记录</li>
        </ol>
      </v-container>
    </v-card-text>
    <v-card-actions>
      <input type="file" accept=".xls,.xlsx" ref="excel_input" hidden />
      <v-btn outlined color="cyan" @click="inputEle().click()">
        <v-icon>mdi-microsoft-excel</v-icon>
      </v-btn>
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import { DataBase } from "@/util/data";
import { CellValue, Workbook } from "exceljs";
import Vue from "vue";

export default Vue.extend({
  name: "load_excel",

  props: {
    load: Function,
  },

  mounted() {
    // event on input file
    const ele = this.inputEle();
    ele.onchange = () => {
      if (ele.files?.length) {
        this.readFile(ele.files[0]);
      }
    };
  },

  methods: {
    inputEle(): HTMLInputElement {
      return this.$refs.excel_input as HTMLInputElement;
    },

    readFile(f: File): void {
      const wb = new Workbook();
      f.arrayBuffer()
        .then((buf) => wb.xlsx.load(buf))
        .then((wb) => {
          this.load(this.collect(wb));
        });
    },

    // parse excel to database
    collect(wb: Workbook): DataBase {
      const db = new DataBase();

      for (const sheet of wb.worksheets) {
        const tb = db.create(
          sheet.name,
          (sheet.getRow(1).values as CellValue[])
            .slice(1)
            .map((e) => (e ? e.toString() : "unknown"))
        );

        sheet.eachRow((row, rowNumber) => {
          if (rowNumber != 1)
            tb.push(
              (row.values as CellValue[])
                .slice(1)
                .map((e) => (e ? e.toString() : "unknown"))
            );
        });
      }

      return db;
    },
  },
});
</script>
