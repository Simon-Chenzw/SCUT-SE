<template>
  <div>
    <v-data-table
      dense
      :headers="headers"
      :items="desserts"
      sort-by="url"
      group-by="hostname"
      class="elevation-1"
      fixed-header
      :items-per-page="100"
      :hide-default-footer="desserts.length <= 100"
    >
      <!-- top -->
      <template v-slot:top>
        <v-toolbar flat>
          <v-toolbar-title>URL Table</v-toolbar-title>
          <v-divider class="mx-4" inset vertical></v-divider>
          <v-spacer></v-spacer>
          <!-- create/edit dialog -->
          <v-dialog v-model="dialog" max-width="500px" persistent>
            <template v-slot:activator="{ on, attrs }">
              <v-btn color="primary" dark class="ml-2" v-bind="attrs" v-on="on">
                New Item
              </v-btn>
            </template>
            <v-card>
              <v-card-title> New Item </v-card-title>
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
                  Cancel
                </v-btn>
                <v-btn
                  color="blue darken-1"
                  text
                  @click="save"
                  :disabled="!isFormValid"
                >
                  Save
                </v-btn>
              </v-card-actions>
            </v-card>
          </v-dialog>
          <!-- exec all -->

          <v-btn color="primary" class="ml-2" @click="exec_all">
            exec all
          </v-btn>

          <!-- delete dialog -->
          <v-dialog v-model="dialogDelete" max-width="500px" persistent>
            <v-card>
              <v-card-title class="text-h5"
                >Are you sure you want to delete this item?</v-card-title
              >
              <v-card-actions>
                <v-spacer></v-spacer>
                <v-btn color="blue darken-1" text @click="closeDelete"
                  >Cancel</v-btn
                >
                <v-btn color="blue darken-1" text @click="deleteItemConfirm"
                  >OK</v-btn
                >
                <v-spacer></v-spacer>
              </v-card-actions>
            </v-card>
          </v-dialog>
        </v-toolbar>
      </template>

      <!-- actions -->
      <template v-slot:[`item.actions`]="{ item }">
        <v-icon small right @click="exec(item)"> mdi-download </v-icon>
        <v-icon
          small
          right
          @click="clear_fund(item)"
          :disabled="item.last_update == 0"
        >
          mdi-broom
        </v-icon>
        <v-icon small right @click="deleteItem(item)"> mdi-delete </v-icon>
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
}

export default Vue.extend({
  // eslint-disable-next-line @typescript-eslint/explicit-module-boundary-types
  data: () => ({
    dialog: false,
    dialogDelete: false,
    headers: [
      { text: "URL", value: "url" },
      { text: "Website Name", value: "hostname" },
      { text: "last update time", value: "last_update_str" },
      { text: "Actions", value: "actions", sortable: false },
    ],
    desserts: [] as ExURLDesc[],
    editedIndex: -1,
    editedItem: { url: "" },
    defaultItem: { url: "" },
    rules: {
      required: (val: string | undefined) => !!val || "Required.",
      counter: (val: string) => val.length <= 100 || "Max 100 characters",
      isURL: (val: string) => {
        try {
          new URL(val)
          return true
        } catch (error) {
          return "Must be a Legal URL"
        }
      },
    },
    isFormValid: false,
    snackbar: false,
    snackbar_text: "",
  }),

  created(): void {
    this.desserts = api_url.select_all()
    this.$data.temp_website = api_website.select_all()
    api_fund.set_exec_callback((resp) => {
      console.log(resp)
      if (resp.status) {
        this.update(resp.url)
      } else {
        console.log(resp.err)
      }
    })
  },

  watch: {
    desserts(val: ExURLDesc[]): void {
      for (const it of val) {
        it.last_update_str = it.last_update
          ? new Date(it.last_update).toLocaleDateString()
          : "Not yet"
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
      // TODO add Visual effect
      api_fund.exec(item.url)
    },

    exec_all(): void {
      // TODO add Visual effect
      for (const item of this.desserts) this.exec(item)
    },

    clear_fund(item: ExURLDesc): void {
      api_fund.clear(item.url)
      this.update(item.url)
    },

    save(): void {
      if (api_url.select(this.editedItem.url)) {
        this.snackbar_text = "URL must be unique."
        this.snackbar = true
      } else {
        const ret = api_url.insert(this.editedItem.url)
        const inserted = api_url.select(this.editedItem.url)
        if (ret && inserted) {
          this.desserts.push(inserted)
        } else {
          this.snackbar_text = "URL's hostname must existed in website"
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
  },
})
</script>
