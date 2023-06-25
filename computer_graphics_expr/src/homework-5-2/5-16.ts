import {
  AmbientLight,
  BackSide,
  BoxGeometry,
  Color,
  LineSegments,
  Mesh,
  MeshPhongMaterial,
  PerspectiveCamera,
  Scene,
  SpotLight,
  WebGLRenderer,
  WireframeGeometry,
} from "three"
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js"

class CubeEdge extends LineSegments {
  constructor(len: number) {
    const geo = new BoxGeometry(len, len, len)
    super(
      new WireframeGeometry(geo),
      new MeshPhongMaterial({
        depthTest: false,
        opacity: 0.25,
        transparent: true,
      })
    )
  }
}

class CubeSurface extends Mesh {
  constructor(len: number, clr: string) {
    super(
      new BoxGeometry(len, len, len),
      new MeshPhongMaterial({
        side: BackSide,
        color: clr,
      })
    )
  }
}

class Cube {
  surface: CubeSurface
  edge: CubeEdge

  constructor(len: number, color: string) {
    this.surface = new CubeSurface(len, color)
    this.edge = new CubeEdge(len)
  }

  add(scene: Scene) {
    scene.add(this.surface, this.edge)
  }

  rotate() {
    this.surface.rotateX(0.01)
    this.surface.rotateY(0.03)
    this.surface.rotateZ(0.05)
    this.edge.rotateX(0.01)
    this.edge.rotateY(0.03)
    this.edge.rotateZ(0.05)
  }
}

const olen = 300,
  ilen = 50,
  llen = 200

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

  private readonly outer = new Cube(olen, "white")
  private readonly inner = new Cube(ilen, "red")

  constructor() {
    this.outer.add(this.scene)
    this.inner.add(this.scene)
    this.inner.surface.castShadow = true
    this.outer.surface.receiveShadow = true

    const ambient = new AmbientLight("white", 0.3)
    this.scene.add(ambient)

    const add_light = (x: number, y: number, z: number) => {
      const light = new SpotLight()
      light.angle = Math.PI / 10
      light.position.set(x, y, z)
      light.target = this.inner.surface
      light.castShadow = true
      this.scene.add(light)
    }
    add_light(llen, 0, 0)
    add_light(0, llen, 0)
    add_light(0, 0, llen)

    this.controls.target.set(0, 0, 0)
    this.controls.object.position.set(200, 250, 300)
    this.controls.update()

    this.renderer.shadowMap.enabled = true
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
    this.inner.rotate()
    this.renderer.render(this.scene, this.camera)
    this.adjustCanvasSize()
    requestAnimationFrame(() => this.render())
  }
}
