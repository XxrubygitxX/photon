

#version 330 core

out vec4 FragColor;

in vec3 output_color;
in vec2 output_texture_coordinates;

uniform sampler2D texture_sampler;

void main()
{

   FragColor = texture(texture_sampler, output_texture_coordinates) * vec4(output_color, 1.0f);

}