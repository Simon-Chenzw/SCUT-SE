import { ShaderMaterial, Vector3, Vector4, TextureLoader } from "three"

// https://observablehq.com/@camargo/three-js-utah-teapot-with-a-custom-phong-shader-material

const vertexShader = `
varying vec3 Normal;
varying vec3 Position;
varying vec2 vUv;

void main() {
    Normal = normalize(normalMatrix * normal);
    Position = vec3(modelViewMatrix * vec4(position, 1.0));
    vUv = uv;
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
`

const fragmentShader = `
varying vec3 Normal;
varying vec3 Position;
varying vec2 vUv;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;
uniform sampler2D tt;

vec3 phong() {
    vec3 n = normalize(Normal);
    vec3 s = normalize(vec3(LightPosition) - Position);
    vec3 v = normalize(vec3(-Position));
    vec3 r = reflect(-s, n);

    vec3 ambient = Ka;
    vec3 diffuse = Kd * max(dot(s, n), 0.0);
    vec3 specular = Ks * pow(max(dot(r, v), 0.0), Shininess);

    return LightIntensity * (ambient + diffuse + specular);
}

void main() { 
    gl_FragColor = texture2D(tt, vUv) + vec4(phong(), 1.0);
}
`

const DIS = 2000.0

export class LightMaterial extends ShaderMaterial {
  theta: number = 0

  constructor() {
    super({
      uniforms: {
        Ka: { value: new Vector3(0.45, 0.25, 0.15) },
        Kd: { value: new Vector3(0.9, 0.5, 0.3) },
        Ks: { value: new Vector3(0.8, 0.8, 0.8) },
        LightIntensity: { value: new Vector4(0.5, 0.5, 0.5, 1.0) },
        LightPosition: { value: new Vector4(DIS, 0.0, 0.0, 1.0) },
        Shininess: { value: 200.0 },
        tt: {
          value: new TextureLoader().load("static/exp-3/texture.jpg"),
        },
      },
      vertexShader,
      fragmentShader,
    })
  }

  update() {
    this.theta = (this.theta + 0.01) % (Math.PI * 2)
    this.uniforms.LightPosition.value = new Vector4(
      DIS * Math.cos(this.theta),
      DIS * Math.sin(this.theta),
      0.0,
      1.0
    )
  }
}
