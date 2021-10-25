import { AmbientLight, Color, Mesh, PerspectiveCamera, PointLight, Scene, WebGLRenderer } from 'three'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js'
import { LightMaterial } from './material'

export class App {
    private readonly scene = new Scene()
    private readonly renderer = new WebGLRenderer({
        antialias: true,
        precision: 'highp',
        canvas: document.getElementById('main-canvas') as HTMLCanvasElement,
    })
    private readonly camera = new PerspectiveCamera()
    private readonly controls = new OrbitControls(this.camera, this.renderer.domElement)

    constructor() {
        const mesh = new LightMaterial();

        const loader = new GLTFLoader()
        loader.load('./static/exp-1-gltf/scene.gltf', (gltf) => {
            gltf.scene.traverse((obj) => {
                if (obj instanceof Mesh) obj.material = mesh
            })
            this.scene.add(gltf.scene)
        })

        const ambient = new AmbientLight("white", 0.3);
        this.scene.add(ambient);

        const diffuse = new PointLight("blue", 1, 0, 2);
        diffuse.position.set(50, 50, 50);
        this.scene.add(diffuse);

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
    }
}
