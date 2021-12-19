#version 330 core
layout(location = 0) in vec3 aPos;
//layout(location = 1) in vec3 aColor;

layout(location=4) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;
//uniform mat4 transform;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 proMat;

//out vec3 ourColor;
//out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
void main(){
	gl_Position = proMat*viewMat*modelMat*vec4(aPos.x, aPos.y, aPos.z, 1.0);
	FragPos=vec3(modelMat*vec4(aPos,1.0f)).xyz; 
	Normal=mat3(transpose(inverse(modelMat)))*aNormal;
	/*当不均匀拉伸时会，法向量会发生改变，法向量将不是法向量，
	 *所以需要transpose(inverse(modelMat))找到法向量
	 */
//	ourColor=aColor;
	TexCoord=aTexCoord;
}