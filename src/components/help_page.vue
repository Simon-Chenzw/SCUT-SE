<template>
  <div>
    {{ msg }}
  </div>
</template>

<script lang="ts">
import Vue from "vue"

export default Vue.extend({
  name: "help_page",
  data: () => ({
    msg: "help_page",
  }),
})
</script>
