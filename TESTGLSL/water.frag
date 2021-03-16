#ifdef GL_ES
precision mediump float;
#endif

uniform float u_time;
uniform vec2 u_resolution;

void main()
{

 vec2 coord = 6.0 * gl_FragCoord.xy / u_resolution;

  for (int n = 1; n < 8; n++){
    float i = float(n);
    coord += vec2(0.7 / i * sin(i * coord.y + u_time + 0.3 * i) + 0.5, 0.4 / i * sin(coord.x + u_time + 0.8 * i) + 1.9);
  }

  coord *= vec2(0.7 / sin(coord.y + u_time + 0.8) + 0.2, 0.4 / sin(coord.x + u_time + 0.3) + 1.6);

  //vec3 color = vec3(0.3 * sin(coord.x) + 0.5, 0.5 * sin(coord.y) + 0.5, sin(coord.x + coord.y));
  vec3 color = vec3(0.1, 0.5 * sin(coord.y), 0.2);//vec3(red,green,blue)


  gl_FragColor = vec4(color, 1.0);


}