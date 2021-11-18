<template>
  <v-row>
    <v-col cols="6">
      <v-container>
        <load-excel :load="load" />
      </v-container>
    </v-col>
    <v-divider vertical />
    <v-col cols="6">
      <v-container>
        <load-sqlite :load="load" />
      </v-container>
    </v-col>
  </v-row>
</template>

<script lang="ts">
import Vue from "vue";
import load_excel from "./load_excel.vue";
import load_sqlite from "./load_sqlite.vue";

export default Vue.extend({
  name: "load_page",

  props: {
    load: Function,
  },

  components: {
    "load-excel": load_excel,
    "load-sqlite": load_sqlite,
  },
});
</script>
