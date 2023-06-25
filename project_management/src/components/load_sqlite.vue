<template>
  <v-card elevation="2">
    <v-card-title> 读取 sqlite </v-card-title>
    <v-card-text>
      <v-container>
        格式要求：TODO
        <ol>
          <li>1</li>
          <li>2</li>
          <li>3</li>
        </ol>
      </v-container>
    </v-card-text>
    <v-card-actions>
      <v-btn />
    </v-card-actions>
  </v-card>
</template>

<script lang="ts">
import Vue from "vue";

export default Vue.extend({
  name: "load_sqlite",

  props: {
    load: Function,
  },
});
</script>
