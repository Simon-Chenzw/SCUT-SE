// import { App } from './demo';
// import { App } from './homework-2/1';
// import { App } from './homework-2/2';
// import { App } from './homework-2/3';
// import { App } from './exp-1/gltf';
// import { App } from './exp-2/gltf';
// import { App } from "./exp-2/teapot"
// import { App } from "./homework-6/app"
// import { App } from "./exp-3/teapot"
import { App } from "./exp-4/scene"

declare global {
  interface Window {
    app: App
  }
}
window.app = window.app || new App()
