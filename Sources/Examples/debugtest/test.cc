
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>
#include <iostream>
#include <vector>


using namespace std;

int main(int arhc, char* argv[]) {

	auto cameraPos = glm::vec3(0.0f, 0.0f, 5.0f);
	auto cameraLookat = glm::vec3(0.0f);
	auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

//	auto cameraDirection = glm::normalize(cameraLookat - cameraPos);
//	auto cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	auto cameraView = glm::lookAt(cameraPos, cameraLookat, cameraUp);
	auto cameraProjection = glm::perspective(glm::radians(90.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	auto cameraOrtho = glm::ortho(-2.0f, 2.0f, -2.0f, 2.0f, 0.1f, 100.0f);


	

	vector<glm::vec4> nearcube;
	//this is a cube with each length is 1.0f
	nearcube.push_back(glm::vec4(0.0f, 0.2f, -90.0f, 1.0f));
	nearcube.push_back(glm::vec4(0.0f, 0.2f, 4.7f, 1.0f));
//	nearcube.push_back(glm::vec4(-0.0f, 0.5f, -1.0f, 1.0f));
//	nearcube.push_back(glm::vec4(-0.0f, 1.5f, 0.0f,  1.0f));
//	nearcube.push_back(glm::vec4(-0.0f, 1.5f, -1.0f, 1.0f));
//	nearcube.push_back(glm::vec4(-1.0f, 0.5f, 0.0f, 1.0f));
//	nearcube.push_back(glm::vec4(-1.0f, 0.5f, -1.0f, 1.0f));
//	nearcube.push_back(glm::vec4(-1.0f, 1.5f, 0.0f,  1.0f));
//	nearcube.push_back(glm::vec4(-1.0f, 1.5f, -1.0f, 1.0f));
	
	for(auto & v : nearcube){
		glm::vec4 result =  cameraProjection * cameraView * v;
		cout << result.x << "," << result.y << "," << result.z << "," << result.w << endl;
	}
	cout << endl;
	cout << "Screen Coords:" << endl;
	for(auto & v : nearcube){
		glm::vec4 result = cameraProjection * cameraView * v;
		auto w_value = result.w;
		cout << result.x /w_value << "," << result.y /w_value << "," << result.z/ w_value << endl;
	}
	
	cout << cameraView << endl;
	cout << cameraProjection << endl;

	cout << endl;


	glm::vec4 nearPoint(0, 0, -0.15f, 1.0f);
	auto clip = cameraProjection * nearPoint;
	std::cout << "z_clip / w = " << clip.z / clip.w << std::endl;

	return 0;

}