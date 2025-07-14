#ifndef SPCUST_HH
#define SPCUST_HH

#include "CustShader.hh"
#include <GL/glew.h>


class spCust {

public:
    spCust(std::string sourceGeneralVertexPath, std::string sourceGeneralFragmentPath);

    ~spCust(){
        glDeleteShader(generalShader);
    }   
    GLuint getGSP() const { return generalShader; }

private:
    GLuint generalShader;

};




#endif