<template>
  <v-container>
    <!-- https://100px.net/docs/wheel.html -->
    <!-- https://100px.net/demo/wheel.html -->
    <LuckyWheel
      width="500px"
      height="500px"
      ref="wheel"
      :blocks="blocks"
      :prizes="prizes"
      :buttons="buttons"
      @start="startCallBack"
      @end="endCallBack"
    />
  </v-container>
</template>

<script lang="ts">
import Vue from "vue";
import VueLuckyCanvas from "@lucky-canvas/vue";

Vue.use(VueLuckyCanvas);

export default Vue.extend({
  name: "wheel_page",

  props: {
    check: Function,
    show: Function,
  },

  data: () => ({
    blocks: [{ padding: "10px", background: "#869cfa" }],
    buttons: [
      { radius: "50%", background: "#617df2" },
      { radius: "45%", background: "#afc8ff" },
      {
        radius: "40%",
        background: "#869cfa",
        pointer: true,
        fonts: [{ text: "开始\n抽奖", top: "-20px" }],
      },
    ],
    prizes: [
      { fonts: [{ text: "0" }], background: "#e9e8fe" },
      { fonts: [{ text: "1" }], background: "#b8c5f2" },
      { fonts: [{ text: "2" }], background: "#e9e8fe" },
      { fonts: [{ text: "3" }], background: "#b8c5f2" },
      { fonts: [{ text: "4" }], background: "#e9e8fe" },
      { fonts: [{ text: "5" }], background: "#b8c5f2" },
    ],
  }),

  methods: {
    startCallBack() {
      if (this.check()) {
        console.log("wheel start");
        /* eslint-disable  @typescript-eslint/no-explicit-any */
        const wheel = this.$refs.wheel as any;
        wheel.play();
        setTimeout(() => {
          wheel.stop((Math.random() * 8) >> 0);
        }, 5000);
      } else {
        console.log("precheck failed");
      }
    },

    endCallBack() {
      console.log("wheel end");
      this.show();
    },
  },
});
</script>
