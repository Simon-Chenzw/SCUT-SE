<template>
  <div>
    {{ msg }}
    <website-table />
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import website_table from "./website_table.vue"

export default Vue.extend({
  components: {
    "website-table": website_table,
  },
  name: "website_page",
  data: () => ({
    msg: "website_page",
  }),
})
</script>
