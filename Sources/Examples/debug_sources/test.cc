#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
//#include <SDL2/SDL_image.h>
int main(int arhc, char* argv[]) {

	using namespace std;
	string tester = { argv[1] };
	cout << tester << endl;
	if (tester.back() == '/')
		cout << "back is /" << endl;




	return 0;

}