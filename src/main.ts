// import { App } from './demo';
// import { App } from './homework-2/1';
// import { App } from './homework-2/2';
// import { App } from './homework-2/3';
// import { App } from './exp-1/gltf';
// import { App } from './exp-2/gltf';
// import { App } from "./exp-2/teapot"
import { App } from "./homework-5-2/5-16"

declare global {
  interface Window {
    app: App
  }
}
window.app = window.app || new App()
