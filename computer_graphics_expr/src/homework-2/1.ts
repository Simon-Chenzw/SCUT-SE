import {
  Color,
  Mesh,
  PerspectiveCamera,
  Scene,
  Vector3,
  WebGLRenderer,
  Shape,
  MeshBasicMaterial,
  ShapeGeometry,
} from "three"

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

  constructor() {
    const shape = new Shape()
    shape.moveTo(-100, -100)
    shape.lineTo(100, -100)
    shape.lineTo(0, 100)
    this.scene.add(
      new Mesh(
        new ShapeGeometry(shape),
        new MeshBasicMaterial({ color: new Color("rgb(0,255,0)") })
      )
    )

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
  }
}
