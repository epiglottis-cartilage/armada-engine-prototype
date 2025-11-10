#define GLM_ENABLE_EXPERIMENTAL
#include <iostream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/string_cast.hpp>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char** argv){

    using std::cout, std::endl;
    glm::vec4 mypoint = {0.0f, 0.0f, -1.0f, 1.0f};

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    cout << glm::to_string(translate) << endl;

    glm::mat4 rotate = glm::yawPitchRoll(glm::radians(0.0f), glm::radians(0.0f), glm::radians(0.0f));
    cout << glm::to_string(rotate) << endl;

    mypoint = translate * rotate * mypoint;

    cout << glm::to_string(mypoint) << endl;

    return 0;


}