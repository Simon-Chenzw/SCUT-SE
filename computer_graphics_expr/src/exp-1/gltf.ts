import {
  Color,
  PerspectiveCamera,
  Scene,
  WebGLRenderer,
  Mesh,
  ShaderMaterial,
} from "three"
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js"
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js"

const vertexShader = `
uniform float delta;

void main()
{
    vec3 p = position.xyz;
    float new_x = p.x*cos(delta) - p.y*sin(delta);
    float new_y = p.y*cos(delta) + p.x*sin(delta);
    
    gl_Position = projectionMatrix * modelViewMatrix * vec4(new_x, new_y, p.z, 1.0);
}
`

const fragmentShader = `
uniform float delta;

void main() {
    float co = cos(delta) / 2.0 + 0.5;
    float si = sin(delta) / 2.0 + 0.5;

    gl_FragColor = vec4(co, si, 0.0, 1.0);
}
`

class CustomMaterial extends ShaderMaterial {
  constructor() {
    super({
      uniforms: {
        delta: { value: 0 },
      },
      vertexShader: vertexShader,
      fragmentShader: fragmentShader,
    })
  }

  update() {
    this.uniforms.delta.value += 0.002
    if (this.uniforms.delta.value > 2 * Math.PI) this.uniforms.delta.value = 0
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
  private readonly material = new CustomMaterial()

  constructor() {
    const loader = new GLTFLoader()
    loader.load("./static/exp-1-gltf/scene.gltf", (gltf) => {
      gltf.scene.traverse((obj) => {
        if (obj instanceof Mesh) obj.material = this.material
      })
      this.scene.add(gltf.scene)
      this.render()
    })

    this.controls.target.set(
      11.29808356545446,
      84.11149570769874,
      -32.04546811190756
    )
    this.controls.object.position.set(
      -6.150562917175668,
      106.5421475924987,
      92.23731894458317
    )
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
    this.material.update()
  }
}
