<template>
  <div>
    {{ msg }}
    <script-editor />
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import script_editor from "./script_editor.vue"

export default Vue.extend({
  components: {
    "script-editor": script_editor,
  },
  name: "script_page",
  data: () => ({
    msg: "script_page",
  }),
})
</script>
