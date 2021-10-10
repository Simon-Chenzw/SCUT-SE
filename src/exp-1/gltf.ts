import { Color, PerspectiveCamera, Scene, WebGLRenderer, Mesh, ShaderMaterial, Vector2 } from 'three'
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'

let vertexShader = `
void main() {
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0); 
}
`

let fragmentShader = `
uniform vec3 color; 

void main() {
    gl_FragColor = vec4(color.r, color.g, color.b, 1.0);
}
`

class CustomMaterial extends ShaderMaterial {
    constructor() {
        super({
            uniforms: {
                color: { value: new Color(0x808080) },
            },
            vertexShader: vertexShader,
            fragmentShader: fragmentShader,
        })
    }

    randColor(from: Color) {
        from.r += (Math.random() - 0.5) * 0.02;
        from.g += (Math.random() - 0.5) * 0.02;
        from.b += (Math.random() - 0.5) * 0.02;
    }

    update() {
        this.randColor(this.uniforms.color.value);
    }
}

export class App {
    private readonly scene = new Scene()
    private readonly renderer = new WebGLRenderer({
        antialias: true,
        precision: 'highp',
        canvas: document.getElementById('main-canvas') as HTMLCanvasElement,
    })
    private readonly camera = new PerspectiveCamera()
    private readonly controls = new OrbitControls(this.camera, this.renderer.domElement)
    private readonly material = new CustomMaterial()

    constructor() {
        const loader = new GLTFLoader()
        loader.load('src/exp-1/scene.gltf', (gltf) => {
            gltf.scene.traverse((obj) => {
                if (obj instanceof Mesh) obj.material = this.material
            })
            this.scene.add(gltf.scene)
            this.render()
        })

        this.controls.target.set(11.29808356545446, 84.11149570769874, -32.04546811190756)
        this.controls.object.position.set(-6.150562917175668, 106.5421475924987, 92.23731894458317)
        this.controls.update()

        this.renderer.setSize(innerWidth, innerHeight)
        this.renderer.setClearColor(new Color('rgb(223, 199, 254)'))
        this.render();
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
        this.material.update();
    }
}
