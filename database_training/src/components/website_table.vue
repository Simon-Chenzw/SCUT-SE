<template>
  <div>
    <v-data-table
      :headers="headers"
      :items="desserts"
      sort-by="name"
      class="elevation-1"
      :hide-default-footer="desserts.length <= 10"
      :disable-pagination="desserts.length <= 10"
    >
      <!-- top -->
      <template v-slot:top>
        <v-toolbar flat>
          <v-toolbar-title> 网站列表 </v-toolbar-title>
          <v-divider class="mx-4" inset vertical></v-divider>
          <v-spacer></v-spacer>
          <!-- create/edit dialog -->
          <v-dialog v-model="dialog" max-width="500px" persistent>
            <template v-slot:activator="{ on, attrs }">
              <v-btn color="primary" dark class="mb-2" v-bind="attrs" v-on="on">
                新建
              </v-btn>
            </template>
            <v-card>
              <v-card-title>
                {{ editedIndex === -1 ? "新建记录" : "修改记录" }}
              </v-card-title>

              <v-card-text>
                <v-container>
                  <v-form v-model="isFormValid">
                    <v-row>
                      <v-col cols="12">
                        <v-text-field
                          v-model="editedItem.name"
                          :rules="[rules.required, rules.counter]"
                          label="网站名称 （自定义）"
                        ></v-text-field>
                      </v-col>
                      <v-col cols="12">
                        <v-text-field
                          v-model="editedItem.hostname"
                          :rules="[rules.required, rules.counter]"
                          label="网站域名"
                        ></v-text-field>
                      </v-col>
                    </v-row>
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
          <!-- delete dialog -->
          <v-dialog v-model="dialogDelete" max-width="500px" persistent>
            <v-card>
              <v-card-title class="text-h5 justify-center">
                确定要删除网站：“{{ editedItem.name }}” 吗？
              </v-card-title>
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
        <v-icon small class="mr-2" @click="editItem(item)"> mdi-pencil </v-icon>
        <v-icon small @click="deleteItem(item)"> mdi-delete </v-icon>
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
import type { WebsiteDesc } from "../api/typing"

declare const api_website: typeof Tapi_website

export default Vue.extend({
  // eslint-disable-next-line @typescript-eslint/explicit-module-boundary-types
  data: () => ({
    dialog: false,
    dialogDelete: false,
    headers: [
      { text: "名称", value: "name" },
      { text: "网站域名", value: "hostname" },
      { text: "操作", value: "actions", sortable: false },
    ],
    desserts: [] as WebsiteDesc[],
    editedIndex: -1,
    editedItem: {
      name: "",
      hostname: "",
    },
    defaultItem: {
      name: "",
      hostname: "",
    },
    rules: {
      required: (val: string | undefined) => !!val || "必填项.",
      counter: (val: string) => val.length <= 100 || "最长 100 字符",
    },
    isFormValid: false,
    snackbar: false,
    snackbar_text: "",
  }),

  created(): void {
    this.desserts = api_website.select_all()
  },

  methods: {
    editItem(item: WebsiteDesc): void {
      this.editedIndex = this.desserts.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialog = true
    },

    save(): void {
      if (this.editedIndex > -1) {
        const ret = api_website.update(
          this.desserts[this.editedIndex].name,
          this.editedItem
        )
        if (ret) {
          Object.assign(this.desserts[this.editedIndex], this.editedItem)
        } else {
          this.snackbar_text = "名称和域名不能相同"
          this.snackbar = true
        }
      } else {
        const ret = api_website.insert(this.editedItem)
        if (ret) {
          this.desserts.push(this.editedItem)
        } else {
          this.snackbar_text = "名称和域名不能相同"
          this.snackbar = true
        }
      }
      this.close()
    },

    close(): void {
      this.dialog = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },

    deleteItem(item: WebsiteDesc): void {
      this.editedIndex = this.desserts.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialogDelete = true
    },

    deleteItemConfirm(): void {
      api_website.remove(this.desserts[this.editedIndex].name)
      this.desserts.splice(this.editedIndex, 1)
      this.closeDelete()
    },

    closeDelete(): void {
      this.dialogDelete = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },
  },
})
</script>
