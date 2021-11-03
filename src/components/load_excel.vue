<template>
  <v-container>
    <template>
      <v-container> `TODO: excel requirement here` </v-container>
      <v-row>
        <v-col cols="7">
          <v-container>
            <input type="file" accept=".xls,.xlsx" ref="excel_input" />
          </v-container>
        </v-col>
        <v-spacer />
        <v-col cols="4">
          <v-container>
            <v-btn outlined color="cyan" @click="solve">
              <v-icon>mdi-checkbox-marked-circle-outline</v-icon>
            </v-btn>
          </v-container>
        </v-col>
      </v-row>
    </template>
  </v-container>
</template>

<script lang="ts">
import Vue from "vue";
import { CellValue, Workbook } from "exceljs";
import { DataBase } from "@/util/data";

export default Vue.extend({
  name: "load_excel",

  props: {
    load: Function,
  },

  mounted() {
    const db = this.loadLocal();
    if (db) {
      console.log("reuse excel in local");
      this.load(db);
    }
  },

  data: () => ({
    excel: undefined as number | undefined,
  }),

  methods: {
    saveLocal(db: DataBase): void {
      window.localStorage.setItem("save_type", "excel");
      window.localStorage.setItem("execl_save", JSON.stringify(db));
    },

    loadLocal(): DataBase | null {
      if (window.localStorage.getItem("save_type") != "excel") {
        return null;
      }
      const save = window.localStorage.getItem("execl_save");
      return save && JSON.parse(save);
    },

    solve(): void {
      const ele = this.$refs.excel_input as HTMLInputElement;
      if (ele.files?.length) {
        const wb = new Workbook();
        ele.files[0]
          .arrayBuffer()
          .then((buf) => wb.xlsx.load(buf))
          .then((wb) => {
            const db = this.collect(wb);
            this.saveLocal(db);
            this.load(db);
          });
      }
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
