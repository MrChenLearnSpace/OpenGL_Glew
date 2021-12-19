#version 330 core

out vec4 FragColor;	

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};
struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};
struct LightPoint{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
};
struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
    float constant;
    float linear;
    float quadratic;
	float cosPhyInner;
	float cosPhyOutter;
};
uniform LightDirectional lightD;
uniform LightPoint lightP1;
uniform LightPoint lightP2;
uniform LightPoint lightP3;
uniform LightPoint lightP4;
uniform LightSpot lightS;
uniform vec3 ambientColor;
uniform vec3 cameraPos;
uniform Material material;

vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera){
	vec3 result=vec3(0,0,0);
	//diffuse
	float diffuseIntensity=max(dot(light.dirToLight,uNormal),0);
	vec3 diffColor=diffuseIntensity*light.color*texture(material.diffuse,TexCoord).rgb;
	result+=diffColor;
	//specular
	vec3 R=normalize(reflect(-light.dirToLight,uNormal));
	float specularIntersity=pow(max(dot(R,dirToCamera),0),material.shininess);
	vec3 specular=specularIntersity*light.color*texture(material.specular,TexCoord).rgb;	
	result+=specular;
	return  result;
}
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera){
	vec3 result=vec3(0,0,0);
	float distances = length(light.pos-FragPos);
	float attenuation=1.0f/(light.constant+light.linear*distances+light.quadratic*distances*distances);
	float diffuseIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0);
	vec3 diffuse=diffuseIntensity*texture(material.diffuse,TexCoord).rgb*light.color;
	result+=diffuse;
	float specularIntersity=pow(max(dot(normalize(reflect(-normalize(light.pos-FragPos),uNormal)),dirToCamera),0),material.shininess);
	vec3 specular=specularIntersity*light.color*texture(material.specular,TexCoord).rgb;
	result += specular;
	result*=attenuation;
	return result;
}
vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera){
	vec3 result=vec3(0,0,0);
	//attenuation
	float distances= length(light.pos - FragPos);
	float attenuation=1.0f/(light.constant+light.linear*distances+light.quadratic*distances*distances);
	float spotRatio=0;
	float cosTheta=dot(normalize(FragPos-light.pos),-1.0f*light.dirToLight);
	//cosTheta=1;
	if(cosTheta > light.cosPhyInner)
	{
		spotRatio=1.0f;
	}else if(cosTheta > light.cosPhyOutter){
		//spotRatio=1.0f-(cosTheta-light.cosPhyInner)/(light.cosPhyOutter-light.cosPhyInner);
		spotRatio=(light.cosPhyOutter-cosTheta)/(light.cosPhyOutter - light.cosPhyInner);
	}
	else{
		spotRatio=0.0f;
	}
	attenuation*=spotRatio;
	//diffuse
	float diffuseIntensity=max(dot(normalize(light.pos-FragPos),uNormal),0);
	vec3 diffuse=texture(material.diffuse,TexCoord).rgb*light.color*diffuseIntensity;
	result+=diffuse;

	//specular
	float specularIntersity=pow(max(dot(normalize(reflect(-normalize(light.pos-FragPos),uNormal)),dirToCamera),0),material.shininess);
	vec3 specular = specularIntersity*texture(material.specular,TexCoord).rgb*light.color;
	result+=specular;
	//result*=attenuation;
	result*=spotRatio;
	return result;
}

void main(){
	vec3 finalResult=vec3(0,0,0);
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);
	vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;
	finalResult+=ambient;
	finalResult += CalcLightDirectional( lightD, uNormal , dirToCamera);
	finalResult += CalcLightPoint(lightP1,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP2,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP3,uNormal,dirToCamera);
	finalResult += CalcLightPoint(lightP4,uNormal,dirToCamera);
	finalResult += CalcLightSpot(lightS,uNormal,dirToCamera);
	FragColor=vec4(finalResult,1.0f);
}