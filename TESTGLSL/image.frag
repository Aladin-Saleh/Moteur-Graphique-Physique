#ifdef GL_ES
precision mediump float;
#endif


uniform float u_time;
uniform vec2 u_resolution;

uniform sampler2D u_tex0;//permet l'affichage d'une image

void main()
{
    vec2 position = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    gl_FragColor = texture2D(u_tex0,position);

}   