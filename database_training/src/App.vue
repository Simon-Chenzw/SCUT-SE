<template>
  <v-app>
    <v-navigation-drawer app permanent class="elevation-3">
      <v-list-item>
        <v-list-item-content>
          <v-list-item-title class="text-h6">
            投资组合评比器
          </v-list-item-title>
          <v-list-item-subtitle> Fund Analysis </v-list-item-subtitle>
        </v-list-item-content>
      </v-list-item>

      <v-divider></v-divider>

      <v-list dense nav>
        <v-list-item
          v-for="item in items"
          :key="item.title"
          link
          @click="current = item.title"
        >
          <v-list-item-icon>
            <v-icon>
              {{ item.icon }}
            </v-icon>
          </v-list-item-icon>

          <v-list-item-content>
            <v-list-item-title>
              {{ item.desc || item.title }}
            </v-list-item-title>
          </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>

    <v-main>
      <v-container>
        <template v-if="current == 'Init' || current == 'Fund'">
          <fund-page />
        </template>
        <template v-else-if="current == 'Website'">
          <website-page />
        </template>
        <template v-else-if="current == 'URL'">
          <url-page />
        </template>
        <template v-else-if="current == 'Script'">
          <script-page />
        </template>
        <template v-else> !! Error: current={{ current }} </template>
      </v-container>
    </v-main>
  </v-app>
</template>

<script lang="ts">
import Vue from "vue"
import fund_page from "./components/fund_page.vue"
import url_page from "./components/url_page.vue"
import website_page from "./components/website_page.vue"
import script_page from "./components/script_page.vue"

export default Vue.extend({
  name: "App",

  components: {
    "fund-page": fund_page,
    "website-page": website_page,
    "url-page": url_page,
    "script-page": script_page,
  },

  data: () => ({
    items: [
      { title: "Fund", icon: "mdi-chart-multiple", desc: "基金浏览" },
      { title: "Website", icon: "mdi-feature-search", desc: "网站录入" },
      { title: "URL", icon: "mdi-link", desc: "URL管理" },
      { title: "Script", icon: "mdi-file-code-outline", desc: "脚本编辑" },
    ],
    current: "Init",
  }),
})
</script>

<style>
html {
  overflow-y: auto;
}
</style>
