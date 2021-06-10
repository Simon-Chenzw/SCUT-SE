<template>
  <div>
    <v-data-table
      dense
      :headers="headers"
      :items="desserts"
      sort-by="url"
      group-by="域名"
      class="elevation-1"
      fixed-header
      :items-per-page="100"
      :hide-default-footer="desserts.length <= 100"
    >
      <!-- top -->
      <template v-slot:top>
        <v-toolbar flat>
          <v-toolbar-title>URL 列表</v-toolbar-title>
          <v-divider class="mx-4" inset vertical></v-divider>
          <v-spacer></v-spacer>
          <!-- create/edit dialog -->
          <v-dialog v-model="dialog" max-width="500px" persistent>
            <template v-slot:activator="{ on, attrs }">
              <v-btn color="primary" dark class="ml-2" v-bind="attrs" v-on="on">
                新建 URL
              </v-btn>
            </template>
            <v-card>
              <v-card-title> 新建 URL </v-card-title>
              <v-card-text>
                <v-container>
                  <v-form v-model="isFormValid">
                    <v-text-field
                      v-model="editedItem.url"
                      :rules="[rules.required, rules.counter, rules.isURL]"
                      label="URL"
                    ></v-text-field>
                  </v-form>
                </v-container>
              </v-card-text>

              <v-card-actions>
                <v-spacer></v-spacer>
                <v-btn color="blue darken-1" text @click="close">
                  <v-icon> mdi-close-circle </v-icon>
                  取消
                </v-btn>
                <v-btn
                  color="blue darken-1"
                  text
                  @click="save"
                  :disabled="!isFormValid"
                >
                  <v-icon> mdi-content-save </v-icon>
                  保存
                </v-btn>
              </v-card-actions>
            </v-card>
          </v-dialog>
          <!-- exec all -->

          <v-btn color="primary" class="ml-2" @click="exec_all">
            爬取全部
          </v-btn>

          <!-- delete dialog -->
          <v-dialog v-model="dialogDelete" max-width="500px" persistent>
            <v-card>
              <v-card-title class="text-h5">
                确定要删除这个 URL ?
              </v-card-title>
              <v-card-text class="text-h6"> {{ editedItem.url }} </v-card-text>
              <v-card-actions>
                <v-spacer></v-spacer>
                <v-btn color="blue darken-1" text @click="closeDelete">
                  取消
                  <v-icon right> mdi-cancel </v-icon>
                </v-btn>
                <v-btn color="blue darken-1" text @click="deleteItemConfirm">
                  确定
                  <v-icon right> mdi-check </v-icon>
                </v-btn>
                <v-spacer></v-spacer>
              </v-card-actions>
            </v-card>
          </v-dialog>
        </v-toolbar>
      </template>

      <!-- actions -->
      <template v-slot:[`item.actions`]="{ item }">
        <!-- crawl -->
        <v-tooltip bottom>
          <template v-slot:activator="{ on, attrs }">
            <v-icon small right @click="exec(item)" v-bind="attrs" v-on="on">
              mdi-download
            </v-icon>
          </template>
          <span> 爬取数据 </span>
        </v-tooltip>
        <!-- clear -->
        <v-tooltip bottom>
          <template v-slot:activator="{ on, attrs }">
            <v-icon
              small
              right
              @click="clear_fund(item)"
              :disabled="item.last_update == 0"
              v-bind="attrs"
              v-on="on"
            >
              mdi-broom
            </v-icon>
          </template>
          <span> 清除数据 </span>
        </v-tooltip>
        <!-- remove -->
        <v-tooltip bottom>
          <template v-slot:activator="{ on, attrs }">
            <v-icon
              small
              right
              @click="deleteItem(item)"
              v-bind="attrs"
              v-on="on"
            >
              mdi-delete
            </v-icon>
          </template>
          <span> 删除记录 </span>
        </v-tooltip>
      </template>
    </v-data-table>
    <v-snackbar v-model="snackbar" :timeout="2000">
      {{ snackbar_text }}
    </v-snackbar>
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import type * as Tapi_website from "../api/api_website"
import type * as Tapi_url from "../api/api_url"
import type * as Tapi_fund from "../api/api_fund"
import type { URLDesc } from "../api/typing"

declare const api_website: typeof Tapi_website
declare const api_url: typeof Tapi_url
declare const api_fund: typeof Tapi_fund

interface ExURLDesc extends URLDesc {
  last_update_str?: string
  域名?: string
}

export default Vue.extend({
  // eslint-disable-next-line @typescript-eslint/explicit-module-boundary-types
  data: () => ({
    dialog: false,
    dialogDelete: false,
    headers: [
      { text: "URL", value: "url" },
      { text: "网站域名", value: "域名" },
      { text: "数据最后时间", value: "last_update_str" },
      { text: "操作", value: "actions", sortable: false },
    ],
    desserts: [] as ExURLDesc[],
    editedIndex: -1,
    editedItem: { url: "" },
    defaultItem: { url: "" },
    rules: {
      required: (val: string | undefined) => !!val || "必填项.",
      counter: (val: string) => val.length <= 100 || "最长 100 字符",
      isURL: (val: string) => {
        try {
          new URL(val)
          return true
        } catch (error) {
          return "必须是合法的URL"
        }
      },
    },
    isFormValid: false,
    snackbar: false,
    snackbar_text: "",
    enable_exec_alert: true,
  }),

  created(): void {
    this.desserts = api_url.select_all()
    for (const it of this.desserts) it.域名 = it.hostname
    this.$data.temp_website = api_website.select_all()
    api_fund.set_exec_callback((resp) => {
      console.log(resp)
      if (resp.status) {
        this.update(resp.url)
        if (this.enable_exec_alert) this.alert(`爬取成功`)
      } else {
        if (this.enable_exec_alert) this.alert(`爬取失败 ${resp.err?.message}`)
        console.log(resp.err)
      }
    })
  },

  destroyed(): void {
    api_fund.rm_exec_callback()
  },

  watch: {
    desserts(val: ExURLDesc[]): void {
      for (const it of val) {
        it.last_update_str = it.last_update
          ? new Date(it.last_update).toLocaleDateString()
          : "尚未爬取"
        it.域名 = it.hostname
      }
    },
  },

  methods: {
    get_index(url: string): number {
      this.desserts.forEach((item, index) => {
        if (item.url == url) return index
      })
      return -1
    },

    update(url: string): void {
      this.desserts.forEach((item, index) => {
        if (item.url == url) {
          const desc = api_url.select(this.desserts[index].url)
          if (desc) this.$set(this.desserts, index, desc)
          return
        }
      })
    },

    exec(item: ExURLDesc): void {
      this.alert(`爬取 ${item.url}`)
      this.enable_exec_alert = true
      const hostname = new URL(item.url).hostname
      if (api_website.get_script_hostname(hostname) === null) {
        this.alert(`${hostname} 没有爬虫脚本`)
        return
      }
      api_fund.exec(item.url)
    },

    exec_all(): void {
      this.alert("爬取全部 URL")
      this.enable_exec_alert = false
      api_fund.exec_all()
    },

    clear_fund(item: ExURLDesc): void {
      api_fund.clear(item.url)
      this.update(item.url)
    },

    save(): void {
      const ret = api_url.insert(this.editedItem.url)
      const inserted = api_url.select(this.editedItem.url)
      if (ret && inserted) {
        this.desserts.push(inserted)
      } else {
        this.alert("URL 不能相同.")
      }
      this.close()
    },

    close(): void {
      this.dialog = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },

    deleteItem(item: ExURLDesc): void {
      this.editedIndex = this.desserts.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialogDelete = true
    },

    deleteItemConfirm(): void {
      api_url.remove(this.desserts[this.editedIndex].url)
      this.desserts.splice(this.editedIndex, 1)
      this.closeDelete()
    },

    closeDelete(): void {
      this.dialogDelete = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },

    alert(msg: string): void {
      this.snackbar = false
      this.snackbar_text = msg
      this.snackbar = true
    },
  },
})
</script>
