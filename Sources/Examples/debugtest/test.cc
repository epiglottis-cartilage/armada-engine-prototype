#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace std;

int main(int arhc, char* argv[]) {

	auto cameraPos = glm::vec3(1.0f, 0.0f, 1.0f);
	auto cameraLookat = glm::vec3(0.0f);
	auto cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	auto cameraDirection = glm::normalize(cameraPos - cameraLookat);
	auto cameraRight = glm::normalize(glm::cross(cameraUp, cameraDirection));

	auto cameraView = glm::lookAt(cameraPos, cameraLookat, cameraUp);
	auto cameraProjection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
	auto cameraOrtho = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);


	auto objectA = glm::vec3(-1.0f, 0.0f, -1.0f);
	auto objectB = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec4 result = cameraProjection * cameraView * glm::vec4(objectA, 1.0f);

	cout << result.x << " " << result.y << " " << result.z << " " << result.w << endl;
	return 0;

}