import { AmbientLight, Color, Mesh, PerspectiveCamera, PointLight, Scene, WebGLRenderer } from 'three';
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js';
import { TeapotGeometry } from 'three/examples/jsm/geometries/TeapotGeometry';
import { LightMaterial } from './material';

class Teapot extends Mesh {
    constructor() {
        const geometry = new TeapotGeometry(400, 15);
        super(geometry, new LightMaterial());
    }
}

export class App {
    private readonly scene = new Scene()
    private readonly renderer = new WebGLRenderer({
        antialias: true,
        precision: 'highp',
        canvas: document.getElementById('main-canvas') as HTMLCanvasElement,
    })
    private readonly camera = new PerspectiveCamera(45, innerWidth / innerHeight, 1, 100000)
    private readonly controls = new OrbitControls(this.camera, this.renderer.domElement)

    constructor() {
        const teapot = new Teapot();
        this.scene.add(teapot);

        const ambient = new AmbientLight("white", 0.3);
        this.scene.add(ambient);

        const diffuse = new PointLight("blue", 1, 0, 2);
        diffuse.position.set(50, 50, 50);
        this.scene.add(diffuse);

        this.controls.target.set(0, 0, 0);
        this.controls.object.position.set(1000, 1000, 1500);
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
