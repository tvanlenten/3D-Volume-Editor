#version 430 core

#define ERROR 0.1

in vec2 uv;
in vec3 uvw;
out vec4 FragColor;

uniform vec3 camera;
uniform float MAX_DIST;
uniform float PRECIS;
uniform int MAX_RAY_STEPS;

uniform float ampA;
uniform float feqA;
uniform float ampB;
uniform float feqB;
uniform float ampC;
uniform float feqC;
uniform float ampD;
uniform float feqD;
uniform float ampE;
uniform float feqE;
uniform vec3 offset;


float min3(vec3 x) {
	return min(min(x.x,x.y),x.z);
}

float max3(vec3 x) {
	return max(max(x.x,x.y),x.z);
} 

float hash(vec3 p) {
    p  = fract( p*0.3183099+.1 );
	p *= 17.0;
    return fract( p.x*p.y*p.z*(p.x+p.y+p.z) );
}
float noise( in vec3 x ) {
    vec3 p = floor(x);
    vec3 f = fract(x);
    f = f*f*(3.0-2.0*f);
	
    return mix(mix(mix( hash(p+vec3(0,0,0)), 
                        hash(p+vec3(1,0,0)),f.x),
                   mix( hash(p+vec3(0,1,0)), 
                        hash(p+vec3(1,1,0)),f.x),f.y),
               mix(mix( hash(p+vec3(0,0,1)), 
                        hash(p+vec3(1,0,1)),f.x),
                   mix( hash(p+vec3(0,1,1)), 
                        hash(p+vec3(1,1,1)),f.x),f.y),f.z);
}

float sdSphere(vec3 p, float r) {
	return length(p) - r;
}

float map(vec3 p) {
	p += offset;
	float d = p.y - 0.5;

	d += noise(p*feqA)*ampA;
	d += noise(p*feqB)*ampB;
	d += noise(p*feqC)*ampC;
	d += noise(p*feqD)*ampD;
	d += noise(p*feqE)*ampE;

	return d;
}

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

void main() {
	//SET UP RAY

	vec3 ro = camera;
	vec3 rd = normalize(uvw - camera);
	vec3 rs = sign(rd);
	vec3 ri = 1.0 / rd;
	vec3 entry = -rs * 0.5 + 0.5;
	float tMin = max( max3( (entry - ro) * ri), 0.0);
	//if(tMin > MAX_DIST)discard;
	vec3 exit = rs * 0.5 + 0.5;
	float tMax = min3( (exit - ro) * ri);

	//CAST RAY
	float t = castRay(ro, rd, tMin, tMax);


	if(t > 0.0) {
		vec3 hit = ro + rd*t;
		vec3 norm = calcNormal(hit);
		vec3 lightPos = vec3(-0.3,4.0,2.9);
		vec3 lightDir = normalize(lightPos - hit);


		vec3 col = norm;

		vec3 ambient = col;
        //diffuse
        float diff = max(dot(norm,lightDir), 0.0);
        vec3 diffuse = (diff * col);
        //specular
        vec3 refDir = reflect(lightDir, norm);
        float spec = pow(max(dot(rd, refDir),0.0), 32.0);
        vec3 specular = (spec * vec3(0.5));
        col = ambient*0.1 + diffuse*0.9 + specular;

		FragColor = vec4(col, 1.0);
	} else {
		discard;
	}
}