attribute vec3 in_Position;
attribute vec4 in_Color;

varying vec4 ex_Color;
void main()
{
	gl_Position = vec4 ex_Color;
	ex_Color = in_Color;
}