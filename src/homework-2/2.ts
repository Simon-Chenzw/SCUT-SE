import {
  Color,
  Mesh,
  PerspectiveCamera,
  Scene,
  Vector3,
  WebGLRenderer,
  MeshBasicMaterial,
  SphereGeometry,
  Object3D,
} from "three"

export class Sphere extends Mesh {
  constructor() {
    super()

    this.geometry = new SphereGeometry(15 * 5, 32, 16)

    this.material = new MeshBasicMaterial({ color: 0x0088ff, wireframe: true })
  }
}

export class App {
  private readonly scene = new Scene()
  private readonly camera = new PerspectiveCamera(
    45,
    innerWidth / innerHeight,
    0.1,
    10000
  )
  private readonly renderer = new WebGLRenderer({
    antialias: true,
    canvas: document.getElementById("main-canvas") as HTMLCanvasElement,
  })

  private objs: Object3D[]

  constructor() {
    this.objs = [new Sphere()]
    this.scene.add(...this.objs)

    this.camera.position.set(200, 200, 200)
    this.camera.lookAt(new Vector3(0, 0, 0))

    this.renderer.setSize(innerWidth, innerHeight)
    this.renderer.setClearColor(new Color("rgb(0,0,0)"))

    this.render()
  }

  private adjustCanvasSize() {
    this.renderer.setSize(innerWidth, innerHeight)
    this.camera.aspect = innerWidth / innerHeight
    this.camera.updateProjectionMatrix()
  }

  private render() {
    this.renderer.render(this.scene, this.camera)
    requestAnimationFrame(() => this.render())

    this.adjustCanvasSize()
    for (const obj of this.objs) obj.rotateY(0.003)
  }
}
