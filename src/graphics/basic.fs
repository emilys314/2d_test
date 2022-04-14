
#version 460 core
out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
    vec4 pixel_color = texture(ourTexture, TexCoord);
    if (pixel_color.a < 0.1)
        discard;
    FragColor = pixel_color;
}