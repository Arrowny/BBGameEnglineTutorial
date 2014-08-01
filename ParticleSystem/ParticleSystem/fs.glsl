#version 430

in vec2 ex_TexCoor;
out vec4 color;

uniform sampler2D texture;
uniform float time;

void main(void){
	vec4 outp = texture2D(texture, ex_TexCoor)*8;
	
	float red, green, blue;
	
	
	red 	= -0.5 + cos(time*0.4+1.5)*0.5;
	green 	= -0.5 + cos(time*0.6)*sin(time*0.3)*0.35;
	blue 	= -0.5 + sin(time*0.2)*0.5;

	outp.x = outp.x + red;
	outp.y = outp.y + green;
	outp.z = outp.z  + blue;
	
	color = outp;
}