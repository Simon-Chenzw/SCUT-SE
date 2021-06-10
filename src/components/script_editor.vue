<template>
  <div>
    <prism-editor
      class="my-editor"
      v-model="code"
      :highlight="highlighter"
      line-numbers
      @keydown.ctrl.83.prevent.stop="save"
    ></prism-editor>
    <v-snackbar v-model="snackbar" :timeout="2000">
      {{ snackbar_text }}
    </v-snackbar>
  </div>
</template>

<script lang="ts">
import Vue from "vue"
import { PrismEditor } from "vue-prism-editor"
import "vue-prism-editor/dist/prismeditor.min.css"
import Prism from "prismjs"
import "prismjs/components/prism-clike"
import "prismjs/components/prism-javascript"
import "prismjs/themes/prism-tomorrow.css"
import * as Tapi_website from "../api/api_website"

declare const api_website: typeof Tapi_website
const defaultCode = `\
// This is the template for crawler code
// You need to imitate this code to obey the framework's interface

// Tip:
// If your crawler is too complicated to run in this framework, 
// you can start an http service on localhost 
// and then query through this script

// Sorry, but the third-party library you can use seems to be only axios
/* global axios :readonly */ //for type hint

// interface DailyInfo {
//   readonly date: number // timestamp
//   readonly value: number // fund value
// }

/**
 * You must defined an async function named \`get\`
 * @param {string} url    - the url that this crawler need to crawl
 * @return {DaliyInfo[]}  - the fund infomatrion this crawler got
 */
async function get(url) {

  // The following example code is the crawler of danjuan
  const tag = (new RegExp("danjuanapp.com/strategy/([^?/]+)")).exec(url)[1]

  const resp = await axios.get(\`https://danjuanapp.com/djapi/plan/v2/growth/\${tag}?type=2&day=all\`)

  const lst = resp.data.data.fund_nav_growth
  return lst.map((ele) => ({
    date: new Date(ele.date).valueOf(), // Raw data: 2021-1-1
    value: Number(ele.value),           // Raw data: "1.0000"
  }))
}
`

export default Vue.extend({
  props: {
    name: {
      type: String,
      default: "",
    },
  },

  components: {
    PrismEditor,
  },

  data: () => ({
    code: defaultCode,
    snackbar: false,
    snackbar_text: "",
  }),

  watch: {
    name(val: string | undefined) {
      this.load(val)
    },
  },

  created(): void {
    this.load(this.name)
  },

  methods: {
    load(name: string | undefined): void {
      if (name) {
        const code = api_website.get_script_name(name)
        if (code) {
          this.code = code
        } else {
          this.code = defaultCode
          this.alert(`${this.name}'s script in empty, use template`)
        }
      } else {
        this.code = defaultCode
      }
    },

    highlighter(code: string): string {
      return Prism.highlight(code, Prism.languages.js, "js")
    },

    save(): void {
      if (this.name) {
        api_website.save_script(this.name, this.code)
        this.alert("Saved successfully")
      }
    },

    alert(msg: string): void {
      this.snackbar_text = msg
      this.snackbar = true
    },
  },
})
</script>

<style>
.my-editor {
  background: #2d2d2d;
  color: #ccc;

  font-family: Fira code, Fira Mono, Consolas, Menlo, Courier, monospace;
  font-size: 14px;
  line-height: 1.5;
  padding: 5px;
}

.prism-editor__textarea:focus {
  outline: none;
}
</style>
