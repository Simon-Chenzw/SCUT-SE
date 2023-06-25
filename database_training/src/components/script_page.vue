<template>
  <div>
    <v-app-bar app>
      {{ editing ? `当前编辑: ${editing}.js` : "当前展示 template.js" }}
      <v-spacer></v-spacer>
      <v-spacer />
      <!-- website select -->
      <v-tooltip bottom>
        <template v-slot:activator="{ on, attrs }">
          <v-btn
            color="primary ma-2"
            dark
            icon
            @click="edit('')"
            v-bind="attrs"
            v-on="on"
          >
            <v-icon> mdi-file-eye </v-icon>
          </v-btn>
        </template>
        <span> 查看模板脚本 </span>
      </v-tooltip>

      <v-menu offset-y>
        <template v-slot:activator="{ on: menu, attrs }">
          <v-tooltip bottom>
            <template v-slot:activator="{ on: tooltip }">
              <v-btn
                color="primary ma-2"
                dark
                icon
                v-bind="attrs"
                v-on="{ ...tooltip, ...menu }"
              >
                <v-icon> mdi-file-code </v-icon>
              </v-btn>
            </template>
            <span> 选择修改的脚本</span>
          </v-tooltip>
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

      <v-tooltip bottom>
        <template v-slot:activator="{ on, attrs }">
          <v-btn
            color="primary ma-2"
            dark
            @click="editor_save"
            icon
            v-bind="attrs"
            v-on="on"
          >
            <v-icon> mdi-content-save </v-icon>
          </v-btn>
        </template>
        <span> 保存 </span>
      </v-tooltip>
    </v-app-bar>

    <v-container>
      <script-editor :name="this.editing" ref="editor" />
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
      this.editing = name
    },

    editor_save(): void {
      ;(this.$refs.editor as unknown as { save: () => void }).save()
    },
  },
})
</script>
