#version 330

out vec4 color;
in vec4 u_Color;
in vec2 TexCoord;

uniform sampler2D theTexture;

void main()
{
	color = texture(theTexture, TexCoord);
}

