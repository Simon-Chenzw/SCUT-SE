import * as THREE from 'three';


export class tetrahedron extends THREE.Mesh {
    constructor(a: THREE.Vector3, b: THREE.Vector3, c: THREE.Vector3, d: THREE.Vector3) {
        let geometry = new THREE.BufferGeometry()
        geometry.setFromPoints([c, b, a, a, d, c, b, d, a, c, d, b])
        geometry.computeVertexNormals()
        super(geometry, new THREE.MeshNormalMaterial())
    }
}



function split(a: THREE.Vector3, b: THREE.Vector3, c: THREE.Vector3, d: THREE.Vector3, dep: number): tetrahedron[] {
    if (dep == 0) {
        return [new tetrahedron(a, b, c, d)];
    } else {
        const mid = (a: THREE.Vector3, b: THREE.Vector3): THREE.Vector3 => b.clone().sub(a).divideScalar(2).add(a);
        return split(mid(a, a), mid(a, b), mid(a, c), mid(a, d), dep - 1)
            .concat(split(mid(b, a), mid(b, b), mid(b, c), mid(b, d), dep - 1))
            .concat(split(mid(c, a), mid(c, b), mid(c, c), mid(c, d), dep - 1))
            .concat(split(mid(d, a), mid(d, b), mid(d, c), mid(d, d), dep - 1));
    }
}


export class App {
    private readonly scene = new THREE.Scene();
    private readonly camera = new THREE.PerspectiveCamera(45, innerWidth / innerHeight, 0.1, 10000);
    private readonly renderer = new THREE.WebGLRenderer({
        antialias: true,
        canvas: document.getElementById('main-canvas') as HTMLCanvasElement,
    });

    constructor() {
        const len = 100;
        this.scene.add(...split(
            new THREE.Vector3(len, len, len),//a 
            new THREE.Vector3(-len, -len, len),//b
            new THREE.Vector3(-len, len, -len),//c
            new THREE.Vector3(len, -len, -len),//d
            5,
        ))

        this.camera.position.set(200, 200, 200);
        this.camera.lookAt(new THREE.Vector3(0, 0, 0));

        this.renderer.setSize(innerWidth, innerHeight);
        this.renderer.setClearColor(new THREE.Color('rgb(0,0,0)'));

        this.render();
    }

    private adjustCanvasSize() {
        this.renderer.setSize(innerWidth, innerHeight);
        this.camera.aspect = innerWidth / innerHeight;
        this.camera.updateProjectionMatrix();
    }

    private render() {
        this.renderer.render(this.scene, this.camera);
        requestAnimationFrame(() => this.render());

        this.adjustCanvasSize();
    }
}
