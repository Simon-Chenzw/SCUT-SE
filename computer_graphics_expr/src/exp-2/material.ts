import { ShaderMaterial, Vector3, Vector4 } from "three"

// https://observablehq.com/@camargo/three-js-utah-teapot-with-a-custom-phong-shader-material

const vertexShader = `
varying vec3 Normal;
varying vec3 Position;

void main() {
    Normal = normalize(normalMatrix * normal);
    Position = vec3(modelViewMatrix * vec4(position, 1.0));
    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
}
`

const fragmentShader = `
varying vec3 Normal;
varying vec3 Position;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;
uniform vec4 LightPosition;
uniform vec3 LightIntensity;
uniform float Shininess;

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
    gl_FragColor = vec4(phong(), 1.0);
}
`

export class LightMaterial extends ShaderMaterial {
  constructor() {
    super({
      uniforms: {
        Ka: { value: new Vector3(0.9, 0.5, 0.3) },
        Kd: { value: new Vector3(0.9, 0.5, 0.3) },
        Ks: { value: new Vector3(0.8, 0.8, 0.8) },
        LightIntensity: { value: new Vector4(0.5, 0.5, 0.5, 1.0) },
        LightPosition: { value: new Vector4(0.0, 2000.0, 0.0, 1.0) },
        Shininess: { value: 200.0 },
      },
      vertexShader,
      fragmentShader,
    })
  }
}
