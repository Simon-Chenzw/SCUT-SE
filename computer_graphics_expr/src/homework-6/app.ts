import {
  AmbientLight,
  BackSide,
  BoxGeometry,
  Color,
  LineSegments,
  Mesh,
  MeshPhongMaterial,
  PerspectiveCamera,
  PointLight,
  Scene,
  SpotLight,
  WebGLRenderer,
  WireframeGeometry,
} from "three"
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js"

class Cube extends Mesh {
  constructor(len: number, clr: string) {
    super(
      new BoxGeometry(len, len, len),
      new MeshPhongMaterial({
        // side: BackSide,
        specular: "white",
        shininess: 200,
        color: clr,
      })
    )
  }
}

export class App {
  private readonly scene = new Scene()
  private readonly renderer = new WebGLRenderer({
    antialias: true,
    precision: "highp",
    canvas: document.getElementById("main-canvas") as HTMLCanvasElement,
  })
  private readonly camera = new PerspectiveCamera()
  private readonly controls = new OrbitControls(
    this.camera,
    this.renderer.domElement
  )

  private readonly cube = new Cube(100, "white")

  constructor() {
    this.scene.add(this.cube)
    const ambient = new AmbientLight("white", 0.3)
    this.scene.add(ambient)

    const g_light = new PointLight("green", 1)
    g_light.position.set(105, 0, 0)
    this.scene.add(g_light)

    const r_light = new PointLight("red", 1)
    r_light.position.set(0, 105, 0)
    this.scene.add(r_light)

    const b_light = new PointLight("blue", 1)
    b_light.position.set(0, 0, 105)
    this.scene.add(b_light)

    this.controls.target.set(0, 0, 0)
    this.controls.object.position.set(200, 200, 200)
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
    this.renderer.render(this.scene, this.camera)
    this.adjustCanvasSize()
    requestAnimationFrame(() => this.render())
  }
}
