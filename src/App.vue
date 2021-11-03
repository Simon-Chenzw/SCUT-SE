<template>
  <v-app>
    <v-main>
      <v-container>
        <template v-if="!db">
          <load-page :load="loadData" />
        </template>
        <template v-else>
          <v-btn @click="unloadData">rechoice data</v-btn>
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
          <wheel :show="show" :check="wheelPreCheck" />
          <!-- dialog to show result -->
          <v-dialog v-model="dialog" width="500">
            <v-card>
              <v-card-title> this is the result: </v-card-title>
              <v-card-text class="text-h5"> {{ result }} </v-card-text>
            </v-card>
          </v-dialog>
        </template>
      </v-container>
    </v-main>
  </v-app>
</template>

<script lang="ts">
import Vue from "vue";
import load_page from "./components/load_page.vue";
import wheel from "./components/wheel.vue";
import { DataBase, DataTable, DataLine } from "./util/data";

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
    window.app = this;
  },

  methods: {
    loadData(db: DataBase): void {
      console.log("load data", db);
      this.db = db;
    },

    unloadData(): void {
      window.localStorage.setItem("save_type", "None");
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
