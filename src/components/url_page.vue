<template>
  <div>
    {{ msg }}
    <!-- <url-table /> -->
  </div>
</template>

<script lang="ts">
import Vue from "vue"
// import url_table from "./url_table.vue"

export default Vue.extend({
  // components: {
  //   "url-table": url_table,
  // },
  name: "url_page",
  data: () => ({
    msg: "url_page",
  }),
})
</script>
