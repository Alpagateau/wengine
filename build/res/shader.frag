#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;

// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;

// NOTE: Add here your custom variables

const vec2 size = vec2(1000, 450);   // Framebuffer size
const float samples = 5.0;          // Pixels per axis; higher = bigger glow, worse performance
const float quality = 1.2;          // Defines size factor: Lower = smaller glow, better quality
const float offset = 1;
const float frequency = 120;

void main()
{
    vec4 sum = vec4(0);
    vec2 sizeFactor = vec2(1)/size*quality;

    // Texel color fetching from texture sampler
    vec4 source = texture(texture0, fragTexCoord);

    const int range = 2;            // should be = (samples - 1)/2;

    for (int x = -range; x <= range; x++)
    {
        for (int y = -range; y <= range; y++)
        {
            sum += texture(texture0, fragTexCoord + vec2(x, y)*sizeFactor);
        }
    }

    // Calculate final fragment color
    float globalPos = (fragTexCoord.y + offset);
    float wavePos = (1+cos((fract(globalPos) - 0.5)*3.14))/2.0;
    float wavePos2 = cos((fract(globalPos*frequency) - 0.5)*3.14);

    finalColor = ((sum/(samples*samples)) + source)*colDiffuse * wavePos * wavePos2;
}
