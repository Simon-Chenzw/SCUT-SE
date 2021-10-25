import {
  BoxGeometry,
  Color,
  Mesh,
  MeshBasicMaterial,
  PerspectiveCamera,
  Scene,
  Vector3,
  WebGLRenderer,
} from "three"

export class Brick extends Mesh {
  constructor(size: number, color: Color) {
    super()
    this.geometry = new BoxGeometry(size, size, size)
    this.material = new MeshBasicMaterial({ color })
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

  private brick: Brick

  constructor() {
    this.brick = new Brick(100, new Color("rgb(255,0,0)"))
    this.scene.add(this.brick)

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
    this.brick.rotateY(0.03)
  }
}
