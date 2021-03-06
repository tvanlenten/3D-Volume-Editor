#pragma once

#include <string>

std::string rayMarchVertex = std::string("#version 430 core\n"
"layout (location = 0) in vec2 position;\n"
"layout (location = 1) in vec2 texCoords;\n"
"\n"
"out vec2 uv;\n"
"\n"
"void main() {\n"
"\tuv = texCoords;\n"
"    gl_Position = vec4(position, 0.0, 1.0); \n"
"} ");

std::string rayMarchFrag = std::string("#version 430 core\n"
"\n"
"#define ERROR 0.75\n"
"#define MAX_RAY_STEPS 256\n"
"#define PRECIS 0.001\n"
"\n"
"in vec2 uv;\n"
"out vec4 FragColor;\n"
"\n"
"uniform vec3 POS;\n"
"uniform vec3 Uplane;\n"
"uniform vec3 Vplane;\n"
"uniform vec3 DIR;\n"
"\n"
"uniform sampler2D tex;\n"
"\n"
"float S( float d1, float d2 ) {\n"
"    return max(-d2,d1);\n"
"}\n"
"float U( float d1, float d2 ) {\n"
"\treturn min(d1, d2);\n"
"}\n"
"\n"
"float sphere(vec3 p, float s) {\n"
"    return length(p) -s;\n"
"}\n"
"float torus( vec3 p, vec2 t ) {\n"
"    return length( vec2(length(p.xz)-t.x,p.y) )-t.y;\n"
"}\n"
"float cylinder( vec3 p, vec2 h ) {\n"
"  vec2 d = abs(vec2(length(p.xz),p.y)) - h;\n"
"  return min(max(d.x,d.y),0.0) + length(max(d,0.0));\n"
"}\n"
"float box( vec3 p, vec3 b ) {\n"
"    vec3 d = abs(p) - b;\n"
"    return min(max(d.x,max(d.y,d.z)),0.0) + length(max(d,0.0));\n"
"}\n"
"float plane( vec3 p ) {\n"
"\treturn p.y;\n"
"}\n"
"\n"
"float map(vec3 p);\n"
"\n"
"float castRay( vec3 ro, vec3 rd, float tmin, float tmax) {\n"
"    float t = tmin;\n"
"    for( int i=0; i < MAX_RAY_STEPS; i++ ) {\n"
"\t    float tempT = map( ro+rd*t );\n"
"        if( tempT < PRECIS || t > tmax ) break;\n"
"        t += tempT * ERROR;\n"
"    }\n"
"\treturn (t>tmax)? -1.0 : t;\n"
"}\n"
"\n"
"vec3 calcNormal( in vec3 pos ) {\n"
"\tvec2 eps = vec2( 0.001, 0.0 );\n"
"\tvec3 nor = vec3( map(pos+eps.xyy).x - map(pos-eps.xyy).x,\n"
"\t\t\t\t\t map(pos+eps.yxy).x - map(pos-eps.yxy).x,\n"
"    \t\t\t\t map(pos+eps.yyx).x - map(pos-eps.yyx).x);\n"
"\treturn normalize(nor);\n"
"}\n"
"\n"
"vec4 texCube(in sampler2D tex, in vec3 p, in vec3 n ) {\n"
"\tvec4 x = texture( tex, p.yz );\n"
"\tvec4 y = texture( tex, p.zx ); \n"
"\tvec4 z = texture( tex, p.xy );\n"
"\treturn x*abs(n.x) + y*abs(n.y) + z*abs(n.z);\n"
"}\n"
"\n"
"void main() {\n"
"\tvec3 ro = POS;\n"
"\tvec2 cam = 2.0 * uv - 1.0;\n"
"\tvec3 rd = normalize(Uplane*cam.x + Vplane*cam.y + DIR);\n"
"\n"
"\tvec3 col = rd;\n"
"    \n"
"    float t = castRay(ro, rd, 0.01, 50.0);\n"
"    if(t > 0.0) {\n"
"        vec3 hit = ro + rd*t;\n"
"        vec3 norm = calcNormal(hit);\n"
"        \n"
"        vec3 lightPos = vec3(3.0,4.5,-2.0);\n"
"        vec3 lightDir = normalize(lightPos - hit);\n"
"        \n"
"        col = texCube(tex, hit, norm).rgb;\n"
"        vec3 ambient = col;\n"
"        //diffuse\n"
"        float diff = max(dot(norm,lightDir), 0.0);\n"
"        vec3 diffuse = (diff * col);\n"
"        //specular\n"
"        vec3 refDir = reflect(lightDir, norm);\n"
"        float spec = pow(max(dot(rd, refDir),0.0), 32.0);\n"
"        vec3 specular = (spec * vec3(0.5));\n"
"        col = ambient*0.1 + diffuse*0.9 + specular;\n"
"    }\n"
"\t\n"
"\tFragColor = vec4(col, 1.0);\n"
"}");