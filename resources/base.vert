#version 400
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcoord;
layout (location = 3) in vec4 a_color;

out vec3 position;
out vec4 color;
out vec2 texCoord;
out vec3 normal;

void main()
{
   position = a_position;
   normal = normalize(normalMatrix * a_normal);
   texCoord = a_texcoord;
   color = a_color;

   gl_Position = vec4(a_position, 1.0);
}