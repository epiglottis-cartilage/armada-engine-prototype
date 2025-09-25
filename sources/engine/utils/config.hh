#pragma once

#include <common.hh>
#include <string>
#include <yaml-cpp/yaml.h>

#include "configtypes.hh"


NAMESPACE_BEGIN

#define CONFIG_FILE_NAME "engine.cfg"

/*
Config class handler parse engine.yaml. 
After constructing the config class, call instancename.parseConfig() to load the config into public fields,
so that every system can read them and initialized.*/
class Config {
public:
    /*
     */
    Config(string path){
        loadConfig(path);
        configPath = path;
    }

    cfgRenderSystem cfgrendersystem;
    cfgAssetSystem cfgassetsystem;
    cfgAppContext cfgappcontext;
    cfgAudioSystem cfgaudiosystem;
    cfgInputSystem cfginputsystem;
    cfgPhysicsSystem cfgphysicsystem;
    



private:

    void loadConfig(string path){
        rootNode = YAML::LoadFile(path);
    }

    void parseConfig();

    YAML::Node rootNode; // 存储整个YAML的原始数据
    string configPath; // 配置文件路径，用于热重载
};

NAMESPACE_END