
#version 330

layout (location = 0) in vec3 pos;

out vec4 u_Color;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(pos, 1.0f);
	u_Color = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);
}
