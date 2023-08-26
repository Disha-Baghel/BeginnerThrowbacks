#version 330 core

out vec4 fragColor;

in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform sampler2D Sampler;
uniform vec3 lightPos;
uniform vec3 cameraPos;

void main(){

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm,lightDir),0.0);

    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;

    vec3 cameraDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);

    float spec = pow(max(dot(cameraDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * texture(Sampler,UV).rgb;
    fragColor = vec4(result,1.0);
}
