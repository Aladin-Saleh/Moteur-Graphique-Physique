#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

void main(){
    vec2 coord = (gl_FragCoord.xy * 2.0 - u_resolution) / min(u_resolution.x, u_resolution.y);
  coord.x += sin(u_time) + cos(0.5 * 2.9);//position x
  //coord.y += cos(0.9) + sin(u_time * 1.9);
  float color = 0.0;//couleur du fond

  color += 0.1 * (abs(sin(9.0)) * 0.5) / length(coord);
  //en mettant une valeur qui varie dans sin() la lumiere se met à clignoter car on change son intensité

  gl_FragColor = vec4(vec3(color), 1.0);
}