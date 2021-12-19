#version 330 core

out vec4 FragColor;


//in vec2 TexCoord;
//in vec3 ourColor;
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace;

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
struct LightPoint{
    float constant;
    float linear;
    float quadratic;
};
struct LightSpot{
    float cosPhyInner;  
    float cosPhyOutter;  
};
uniform Material material;
uniform LightPoint lightP;
uniform LightSpot lightS;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 lightDirUniform;
uniform vec3 cameraPos;
void main(){
    float distance= length(lightPos-FragPos);
    float attenuation=1.0/(lightP.constant+lightP.linear*distance+lightP.quadratic*(distance*distance));

    vec3 lightDir=normalize(lightPos-FragPos);
    vec3 reflectVec=reflect(-lightDir,Normal);
    vec3 cameraVec=normalize(cameraPos-FragPos);

    //specular
    float specularAmount=pow(max(dot(reflectVec,cameraVec),0),material.shininess); 
    vec3 specular=texture(material.specular,TexCoord).rgb * specularAmount * lightColor;

    //diffuse
    vec3 diffuse=texture(material.diffuse,TexCoord).rgb*max(dot(lightDir,Normal),0)*lightColor;
    //vec3 diffuse=texture(material.diffuse,TexCoord).rgb;
    
    //emission
    vec3 emission=texture(material.emission,TexCoord).rgb;

    //ambient具体能表现无光照区域的颜色，在物体较暗的部分加上漫反射贴图会更真实
    vec3 ambient=texture(material.diffuse,TexCoord).rgb*ambientColor;

    float cosTheta=dot(normalize(FragPos-lightPos),-1*lightDirUniform);
    float spotRatio=1.0f;
    if(cosTheta>lightS.cosPhyInner)//内圈边界是cos函数
    {
       spotRatio=1.0f;  
    }
    else if(cosTheta>lightS.cosPhyOutter)
    {
        spotRatio=1.0f-(cosTheta-lightS.cosPhyInner)/(lightS.cosPhyOutter-lightS.cosPhyInner);//角度数值越大，角越小
    }
    else
    {
         spotRatio=0;
    }
    FragColor =vec4((ambient+(diffuse+specular)*spotRatio)*objColor,1.0f);
//    if(cosTheta > lightS.cosPhy)
//    {
//        FragColor =vec4((ambient+(diffuse+specular))*objColor,1.0f);
//    }else{
//        FragColor =vec4(ambient*objColor,1.0f);
//    }
    //FragColor =vec4((ambient+(diffuse+specular)*attenuation)*objColor,1.0f);
    //教材显示需要让环境光乘上衰减度，傅老师没有加环境光乘上+emission

}