<template>
  <v-app>
    {{ msg }}
  </v-app>
</template>

<script lang="ts">
import Vue from "vue";

export default Vue.extend({
  name: "App",
  data: () => ({
    msg: "hello vue",
  }),
});
</script>
