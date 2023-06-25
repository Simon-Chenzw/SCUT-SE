<template>
  <div>
    <fund-table />
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import fund_table from "./fund_table.vue"

export default Vue.extend({
  components: {
    "fund-table": fund_table,
  },
  name: "fund_page",
  data: () => ({
    msg: "fund_page",
  }),
})
</script>
