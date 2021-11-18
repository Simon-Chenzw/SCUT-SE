<template>
  <v-app>
    <v-app-bar app>
      <v-banner single-line shaped> 幸运大转盘 - lucky wheel </v-banner>
    </v-app-bar>

    <v-main>
      <v-container fluid>
        <template v-if="!db">
          <load-page :load="loadData" />
        </template>
        <template v-else>
          <v-container>
            <v-row>
              <v-col cols="8">
                <wheel :show="show" :check="wheelPreCheck" />
              </v-col>
              <v-col cols="4">
                <v-container>
                  <span> 选择数据表/列： </span>
                  <v-select
                    :items="all_tables"
                    label="table"
                    @change="(v) => (this.selected_table = v)"
                  ></v-select>
                  <v-select
                    :items="all_cols"
                    label="col"
                    @change="(v) => (this.selected_col = v)"
                  ></v-select>
                </v-container>

                <v-divider />

                <v-container>
                  <span> 重新选择数据： </span>
                  <v-btn outlined color="cyan" @click="unloadData">
                    <v-icon>mdi-delete-forever</v-icon>
                  </v-btn>
                </v-container>
              </v-col>
            </v-row>
          </v-container>
          <!-- dialog to show result -->
          <v-dialog v-model="dialog" width="500">
            <v-card>
              <v-card-title> 结果: </v-card-title>
              <v-card-text class="text-h5">
                抽中的是： {{ result }}
              </v-card-text>
            </v-card>
          </v-dialog>
        </template>
      </v-container>
    </v-main>

    <v-footer app>
      <!-- -->
    </v-footer>
  </v-app>
</template>

<script lang="ts">
import Vue from "vue";
import load_page from "./components/load_page.vue";
import wheel from "./components/wheel.vue";
import { DataBase, DataLine, DataTable } from "./util/data";

declare global {
  interface Window {
    app: Vue;
  }
}

function getFromDB(db: DataBase, name: string): DataTable | null {
  for (const ele of db.tables) {
    if (ele.name == name) return ele.table;
  }
  return null;
}

function randLine(tb: DataTable): DataLine {
  return tb.lines[Math.floor(Math.random() * tb.lines.length)];
}

export default Vue.extend({
  name: "App",

  components: { "load-page": load_page, wheel },

  data: () => ({
    db: undefined as DataBase | undefined,

    // for select value
    selected_table: "",
    selected_col: "",

    // for show result
    dialog: false,
    result: "somebody",
  }),

  computed: {
    all_tables(): string[] {
      if (this.db) return this.db.tables.map((ele) => ele.name);
      else return [];
    },

    all_cols() {
      if (this.db) {
        const tb = getFromDB(this.db, this.selected_table);
        if (tb) return tb.header;
      }
      return [];
    },
  },

  mounted() {
    const db = this.loadLocal();
    if (db) {
      console.log("reuse database in local storage");
      this.loadData(db);
    }

    window.app = this;
  },

  methods: {
    saveLocal(db: DataBase): void {
      window.localStorage.setItem("database", JSON.stringify(db));
    },

    loadLocal(): DataBase | null {
      const save = window.localStorage.getItem("database");
      if (save !== null) return DataBase.restore(save);
      else return null;
    },

    loadData(db: DataBase): void {
      console.log("load data", db);
      this.saveLocal(db);
      this.db = db;
    },

    unloadData(): void {
      window.localStorage.removeItem("database");
      console.log("unload data");
      this.db = undefined;
    },

    wheelPreCheck(): boolean {
      if (this.db) {
        const tb = getFromDB(this.db, this.selected_table);
        if (tb) return tb.header.includes(this.selected_col);
      }
      return false;
    },

    show(): void {
      // calc result
      if (this.db) {
        const tb = getFromDB(this.db, this.selected_table);
        if (tb) {
          const line = randLine(tb);
          this.result = line[this.selected_col];
        }
      }
      this.dialog = true;
    },
  },
});
</script>
