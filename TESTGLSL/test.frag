#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;//resolution de la fenetre
uniform float u_time;//DeltaTime


mat2 scale(vec2 scale)
{
    return mat2(scale.x,0.0,0.0,scale.y);
}

mat2 rotate(float angle)
{
    return mat2(cos(angle), -sin(angle), sin(angle), cos(angle));
}


float cercle_shape(vec2 position, float radius)
{
//cercle
    return step(radius, length(position - vec2(0.5)));//length = taille du vecteur
    //sur glsl la coordonnées x = 0, y = 0 se trouve en bas à droite
}

float rect_shape(vec2 position, vec2 scale)
{
    //rectangle
    scale = vec2(0.5) - scale * 0.9;
	vec2 shaper = vec2(step(scale.x, position.x), step(scale.y, position.y));
	shaper *= vec2(step(scale.x, 1.0 - position.x), step(scale.y, 1.0 - position.y));
	return shaper.x * shaper.y;

}

void main()
{
    vec2 position = gl_FragCoord.xy / u_resolution;
    vec2 positionRect = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0, 1.0, 0.749);//set la couleur, même systeme que le rgb compris de 0.0 à 1.0
    vec2 translate = vec2(sin(u_time)*0.5 ,cos(u_time)*0.5);//deplace un objet/model sur un plan à 2 dimensions
    

    position += scale(vec2(0.5,0.2)) * position;//Le scale, il s'agit de l'echelle de rendu du shader
    position += translate;
    float cercle = cercle_shape(position, 1.0);

    positionRect -= vec2(0.5);
    positionRect = rotate(u_time) * positionRect;
    positionRect += vec2(0.5);
    float rectangle = rect_shape(positionRect, vec2(0.3,0.3));

    
    color = vec3(rectangle);
    //color = vec3(cercle);

    gl_FragColor = vec4(color, 1.0);//marche avec vec2 

    

}