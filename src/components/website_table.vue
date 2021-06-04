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
          <v-toolbar-title>Website Table</v-toolbar-title>
          <v-divider class="mx-4" inset vertical></v-divider>
          <v-spacer></v-spacer>
          <!-- create/edit dialog -->
          <v-dialog v-model="dialog" max-width="500px" persistent>
            <template v-slot:activator="{ on, attrs }">
              <v-btn color="primary" dark class="mb-2" v-bind="attrs" v-on="on">
                New Item
              </v-btn>
            </template>
            <v-card>
              <v-card-title>
                {{ editedIndex === -1 ? "New Item" : "Edit Item" }}
              </v-card-title>

              <v-card-text>
                <v-container>
                  <v-form v-model="isFormValid">
                    <v-row>
                      <v-col cols="12" sm="6" md="4">
                        <v-text-field
                          v-model="editedItem.name"
                          :rules="[rules.required, rules.counter]"
                          label="website name"
                        ></v-text-field>
                      </v-col>
                      <v-col cols="12" sm="6" md="4">
                        <v-text-field
                          v-model="editedItem.hostname"
                          :rules="[rules.required, rules.counter]"
                          :disabled="editedIndex !== -1"
                          label="host name"
                        ></v-text-field>
                      </v-col>
                    </v-row>
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
        <v-icon small class="mr-2" @click="editItem(item)"> mdi-pencil </v-icon>
        <v-icon small @click="deleteItem(item)"> mdi-delete </v-icon>
      </template>
    </v-data-table>
    <v-snackbar v-model="snackbar" :timeout="2000">
      {{ snackbar_text }}
    </v-snackbar>
  </div>
</template>

<script>
/* global api_website:readonly */

export default {
  data: () => ({
    dialog: false,
    dialogDelete: false,
    headers: [
      { text: "website name", value: "name" },
      { text: "HostName", value: "hostname" },
      { text: "Actions", value: "actions", sortable: false },
    ],
    desserts: [],
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
      required: (value) => !!value || "Required.",
      counter: (value) => value.length <= 100 || "Max 100 characters",
    },
    isFormValid: false,
    snackbar: false,
    snackbar_text: "",
  }),

  created() {
    this.desserts = api_website.select_all()
  },

  methods: {
    editItem(item) {
      this.editedIndex = this.desserts.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialog = true
    },

    save() {
      if (this.editedIndex > -1) {
        api_website.update(
          this.desserts[this.editedIndex].name,
          this.editedItem
        )
        Object.assign(this.desserts[this.editedIndex], this.editedItem)
      } else {
        const ret = api_website.insert(this.editedItem)
        if (ret) {
          this.desserts.push(this.editedItem)
        } else {
          this.snackbar_text = "values must be unique"
          this.snackbar = true
        }
      }
      this.close()
    },

    close() {
      this.dialog = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },

    deleteItem(item) {
      this.editedIndex = this.desserts.indexOf(item)
      this.editedItem = Object.assign({}, item)
      this.dialogDelete = true
    },

    deleteItemConfirm() {
      api_website.remove(this.desserts[this.editedIndex].name)
      this.desserts.splice(this.editedIndex, 1)
      this.closeDelete()
    },

    closeDelete() {
      this.dialogDelete = false
      this.editedItem = Object.assign({}, this.defaultItem)
      this.editedIndex = -1
    },
  },
}
</script>
