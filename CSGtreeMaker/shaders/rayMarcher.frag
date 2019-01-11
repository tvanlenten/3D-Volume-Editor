#version 430 core

#define ERROR 0.9
#define MAX_RAY_STEPS 128
#define PRECIS 0.01

in vec2 uv;
out vec4 FragColor;

uniform vec3 POS;
uniform vec3 Uplane;
uniform vec3 Vplane;
uniform vec3 DIR;

uniform sampler2D tex;

float S( float d1, float d2 ) {
    return max(-d2,d1);
}
float U( float d1, float d2 ) {
	return min(d1, d2);
}

float sphere(vec3 p, float s) {
    return length(p) -s;
}
float torus( vec3 p, vec2 t ) {
    return length( vec2(length(p.xz)-t.x,p.y) )-t.y;
}
float cylinder( vec3 p, vec2 h ) {
  vec2 d = abs(vec2(length(p.xz),p.y)) - h;
  return min(max(d.x,d.y),0.0) + length(max(d,0.0));
}
float box( vec3 p, vec3 b ) {
    vec3 d = abs(p) - b;
    return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));
}
float plane( vec3 p ) {
	return p.y;
}

float map(vec3 p);

float castRay( vec3 ro, vec3 rd, float tmin, float tmax) {
    float t = tmin;
    for( int i=0; i < MAX_RAY_STEPS; i++ ) {
	    float tempT = map( ro+rd*t );
        if( tempT < PRECIS || t > tmax ) break;
        t += tempT * ERROR;
    }
	return (t>tmax)? -1.0 : t;
}

vec3 calcNormal( in vec3 pos ) {
	vec2 eps = vec2( 0.001, 0.0 );
	vec3 nor = vec3( map(pos+eps.xyy).x - map(pos-eps.xyy).x,
					 map(pos+eps.yxy).x - map(pos-eps.yxy).x,
    				 map(pos+eps.yyx).x - map(pos-eps.yyx).x);
	return normalize(nor);
}

vec4 texCube(in sampler2D tex, in vec3 p, in vec3 n ) {
	vec4 x = texture( tex, p.yz );
	vec4 y = texture( tex, p.zx ); 
	vec4 z = texture( tex, p.xy );
	return x*abs(n.x) + y*abs(n.y) + z*abs(n.z);
}

void main() {
	vec3 ro = POS;
	vec2 cam = 2.0 * uv - 1.0;
	vec3 rd = normalize(Uplane*cam.x + Vplane*cam.y + DIR);

	vec3 col = rd;
    
    float t = castRay(ro, rd, 0.01, 50.0);
    if(t > 0.0) {
        vec3 hit = ro + rd*t;
        vec3 norm = calcNormal(hit);
        
        vec3 lightPos = vec3(3.0,4.5,-2.0);
        vec3 lightDir = normalize(lightPos - hit);
        
        col = texCube(tex, hit, norm).rgb;
        vec3 ambient = col;
        //diffuse
        float diff = max(dot(norm,lightDir), 0.0);
        vec3 diffuse = (diff * col);
        //specular
        vec3 refDir = reflect(lightDir, norm);
        float spec = pow(max(dot(rd, refDir),0.0), 32.0);
        vec3 specular = (spec * vec3(0.5));
        col = ambient*0.1 + diffuse*0.9 + specular;
    }
	
	FragColor = vec4(col, 1.0);
}

float map(vec3 p) {
	return sphere(p, 1.0);
}