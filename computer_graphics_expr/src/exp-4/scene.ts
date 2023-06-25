import {
  Color,
  Mesh,
  PerspectiveCamera,
  Scene,
  WebGLRenderer,
  MeshBasicMaterial,
  DoubleSide,
  PlaneBufferGeometry,
} from "three"
import { GLTF, GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader"
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js"
import { TeapotGeometry } from "three/examples/jsm/geometries/TeapotGeometry"
import { LightMaterial } from "./material"

class Teapot extends Mesh {
  theta: number

  constructor() {
    const geometry = new TeapotGeometry(30, 15)
    super(geometry, new LightMaterial())
    this.theta = 0
    this.position.set(
      100 * Math.cos(this.theta),
      100,
      100 * Math.sin(this.theta)
    )
    document.onkeydown = (e) => {
      switch (e.keyCode) {
        case 37:
          this.rotation.x += 0.1
          break
        case 38:
          this.rotation.z -= 0.1
          break
        case 39:
          this.rotation.x -= 0.1
          break
        case 40:
          this.rotation.z += 0.1
          break
      }
    }
  }

  update() {
    this.theta = (this.theta + 0.01) % (Math.PI * 2)
    this.position.set(
      100 * Math.cos(this.theta),
      100,
      100 * Math.sin(this.theta)
    )
  }
}

class Floor extends Mesh {
  constructor() {
    const geometry = new PlaneBufferGeometry(2000, 2000, 8, 8)
    const material = new MeshBasicMaterial({ color: "grey", side: DoubleSide })
    super(geometry, material)
    this.rotateX(-Math.PI / 2)
    this.position.set(0, 0, 0)
  }
}

export class App {
  private readonly scene = new Scene()
  private readonly renderer = new WebGLRenderer({
    antialias: true,
    precision: "highp",
    canvas: document.getElementById("main-canvas") as HTMLCanvasElement,
  })
  private readonly camera = new PerspectiveCamera(
    45,
    innerWidth / innerHeight,
    1,
    10000
  )
  private readonly controls = new OrbitControls(
    this.camera,
    this.renderer.domElement
  )

  private readonly teapot = new Teapot()
  private readonly floor = new Floor()
  private gltf?: GLTF = undefined

  constructor() {
    this.scene.add(this.teapot)
    this.scene.add(this.floor)

    const loader = new GLTFLoader()
    loader.load("./static/exp-1-gltf/scene.gltf", (gltf) => {
      this.gltf = gltf
      gltf.scene.traverse((obj) => {
        if (obj instanceof Mesh) obj.material = new LightMaterial()
      })
      this.scene.add(gltf.scene)
    })

    this.controls.target.set(0, 0, 0)
    this.controls.object.position.set(300, 300, 300)
    this.controls.update()

    this.renderer.setSize(innerWidth, innerHeight)
    this.renderer.setClearColor(new Color("rgb(223, 199, 254)"))
    this.render()
  }

  private adjustCanvasSize() {
    this.renderer.setSize(innerWidth, innerHeight)
    this.camera.aspect = innerWidth / innerHeight
    this.camera.updateProjectionMatrix()
  }

  private render() {
    this.teapot.update()
    ;(this.teapot.material as LightMaterial).update()
    this.gltf?.scene.traverse((obj) => {
      if (obj instanceof Mesh) (obj.material as LightMaterial).update()
    })
    this.renderer.render(this.scene, this.camera)
    this.adjustCanvasSize()
    requestAnimationFrame(() => this.render())
  }
}
