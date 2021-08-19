#version 330 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPos);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}

/** In the "ShadowMappingDepth.farg" 
|we used an empty fragment shader and let OpenGL figure out the depth values of the depth map. 
|This time we're going to calculate our own (linear) depth as the linear distance between each 
|closest fragment position and the light source's position. Calculating our own depth values 
|makes the later shadow calculations a bit more intuitive.
*/