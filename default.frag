#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 textCoord;
in vec3 Normal;
in vec3 currentPos;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	float ambient = 0.2;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - currentPos);

	float diffuse = max(dot(normal, lightDirection), 0.0);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currentPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmout = pow(max(dot(viewDirection, reflectionDirection), 0.0), 8);
	float specular = specAmout * specularLight;
	
	FragColor = texture(tex0, textCoord) * lightColor * (diffuse + ambient + specular); 
}
