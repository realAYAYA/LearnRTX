#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    /** Perform perspective divide
    |As the clip-space FragPosLightSpace is not passed to the fragment shader through gl_Position, 
    |we have to do this perspective divide ourselves
    */
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    /** Transform to [0,1] range
    |Because the depth from the depth map is in the range [0,1] 
    |and we also want to use projCoords to sample from the depth map, 
    |we transform the NDC coordinates to the range [0,1]:
    */
    projCoords = projCoords * 0.5 + 0.5;

    /** Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)*/
    float closestDepth = texture(shadowMap, projCoords.xy).r; 

    /** Get depth of current fragment from light's perspective*/
    float currentDepth = projCoords.z;

    /** Check whether current frag pos is in shadow*/
    float bias = max(0.05 * (1.0 - dot(fs_in.Normal, lightPos - fs_in.FragPos)), 0.005);
    //float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;

    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    // Keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

void main()
{
    /** BlinnPhong*/
    vec3 color = texture(diffuseTexture, fs_in.TexCoords).rgb;
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightColor = vec3(0.3);
    // ambient
    vec3 ambient = 0.3 * color;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;

    // calculate shadow
    // 1-shadow means how much the fragment is not in shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;
    
    FragColor = vec4(lighting, 1.0);
}