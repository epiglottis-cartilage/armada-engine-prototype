#include <OpenglShader.hh>

NAMESPACE_BEGIN
using namespace std;

CustShader::CustShader(GLenum shadertype, string sourceGeneralVertexPath){
    
    GLchar shaderInfoLog[512];
    GLint success;
    

	#ifdef DEBUG
    cout << "shader path: " << endl;
    cout << sourceGeneralVertexPath << endl;
    namespace fs = std::filesystem;
	// 检查文件是否存在并可访问
	if (!fs::exists(sourceGeneralVertexPath)) {
		std::cerr << "Error: shader file does not exist -> " 
				  << sourceGeneralVertexPath << std::endl;
		//throw std::runtime_error("Shader file not found");
	}
	if (!fs::is_regular_file(sourceGeneralVertexPath)) {
		std::cerr << "Error: shader path is not a regular file -> "
				  << sourceGeneralVertexPath << std::endl;
		//throw std::runtime_error("Shader path invalid");
	}

	// 现在安全地打开文件
	#endif

    ifstream file(sourceGeneralVertexPath);

	#ifdef DEBUG
		if (!file.is_open()) {
			std::cerr << "Error: failed to open shader file -> " 
					  << sourceGeneralVertexPath << std::endl;
			//throw std::runtime_error("Shader file cannot be opened");
		}
	#endif


    string content((istreambuf_iterator<char>(file)), 
        istreambuf_iterator<char>()
    );    

    generalShader = glCreateShader(shadertype);

    const char* sourcesShader = content.c_str();
    glShaderSource(generalShader, 1, &sourcesShader, NULL);
    glCompileShader(generalShader);

    glGetShaderiv(generalShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(generalShader, 512, NULL, shaderInfoLog);
        std::cerr << "Shader compilation failed:\n" << shaderInfoLog << std::endl;
    }
};
optional<GLuint> CustShader::shaderLink(CustShader vertexShader, CustShader fragmentShader){
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader.generalShader);
    glAttachShader(shaderProgram, fragmentShader.generalShader);
    glLinkProgram(shaderProgram);

    GLint cust_errorcode;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &cust_errorcode);

    if (!cust_errorcode) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        glDeleteProgram(shaderProgram);
        return {};
    }
    return {shaderProgram};
}








NAMESPACE_END
