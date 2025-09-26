#include "Config.hh"

NAMESPACE_BEGIN

void Config::parseConfig(){
    bool result = true;


    YAML::Node appcontext = rootNode["generalinfo"];
    appcontext = appcontext["debug"];
    if(appcontext){
        cfgappcontext.consoleoutput = appcontext["console"].as<bool>(cfgappcontext.consoleoutput);
        cfgappcontext.fileoutput = appcontext["logfile"].as<bool>(cfgappcontext.fileoutput);
        cfgappcontext.fileoutputappend = appcontext["logfileappend"].as<bool>(cfgappcontext.fileoutputappend);
    }


    YAML::Node rendersystem = rootNode["rendersystem"];
    if(rendersystem){
        cfgrendersystem.screenwidth = rendersystem["screenwidth"].as<int>(cfgrendersystem.screenwidth);
        this->cfgrendersystem.screenheight = rendersystem["screenheight"].as<int>(cfgrendersystem.screenheight);
        cfgrendersystem.screenmode = rendersystem["screenmode"].as<std::string>(cfgrendersystem.screenmode);
        cfgrendersystem.vsync = rendersystem["vsync"].as<bool>(cfgrendersystem.vsync);



        cfgrendersystem.sdlimg_format = rendersystem["sdlimg_format"].as<std::string>(cfgrendersystem.sdlimg_format);
    }

    YAML::Node assetsystem = rootNode["assetsystem"];
    if(assetsystem){
        cfgassetsystem.assetpath = assetsystem["rootdirectory"].as<std::string>(cfgassetsystem.assetpath);
    }



}

NAMESPACE_END