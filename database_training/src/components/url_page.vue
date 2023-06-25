<template>
  <div>
    <v-app-bar app> 已记录 URL </v-app-bar>
    <url-table />
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import url_table from "./url_table.vue"

export default Vue.extend({
  components: {
    "url-table": url_table,
  },

  name: "url_page",

  data: () => ({}),
})
</script>
