<template>
  <v-row>
    <v-col cols="6">
      <load-excel :load="load" />
    </v-col>
    <v-divider vertical />
    <v-col cols="6">
      <div>TODO: here to load sqlite</div>
    </v-col>
  </v-row>
</template>

<script lang="ts">
import Vue from "vue";
import load_excel from "./load_excel.vue";

export default Vue.extend({
  name: "load_page",

  props: {
    load: Function,
  },

  components: {
    "load-excel": load_excel,
  },
});
</script>
