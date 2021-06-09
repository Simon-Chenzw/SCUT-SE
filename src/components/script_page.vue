<template>
  <div>
    <v-app-bar app>
      <v-spacer></v-spacer>
      <v-menu>
        <template v-slot:activator="{ on, attrs }">
          <v-btn color="primary" dark v-bind="attrs" v-on="on"> select </v-btn>
        </template>
        <v-list>
          <v-list-item
            v-for="(item, index) in this.scripts"
            :key="index"
            @click="edit(item.name)"
          >
            <v-list-item-title> {{ item.name }} </v-list-item-title>
          </v-list-item>
        </v-list>
      </v-menu>
    </v-app-bar>

    <v-container>
      <script-editor :name="this.editing" />
    </v-container>
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import script_editor from "./script_editor.vue"
import type * as Tapi_website from "../api/api_website"
import type { WebsiteDesc } from "../api/typing"

declare const api_website: typeof Tapi_website

export default Vue.extend({
  components: {
    "script-editor": script_editor,
  },

  name: "script_page",

  data: () => ({
    editing: "",
    scripts: [] as WebsiteDesc[],
  }),

  created() {
    this.scripts = api_website.select_all()
  },

  methods: {
    edit(name: string) {
      console.log("name", name)
      this.editing = name
    },
  },
})
</script>

<style>
.div {
  background: #2d2d2d;
}
</style>
