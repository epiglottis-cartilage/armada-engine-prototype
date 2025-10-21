# Armada Engine

A Easy-to-use OOP rendering framework. Currently converting its architecture to fits a game engine.

## Overview & Introductions
Armada Engine (fleet engine) is my personal project aimed at building a high-performance game engine tailored for first-person and third-person shooter titles. 

### Implemented Features
- **Simple Rendering Layer**: Currently using OpenGL 460 (Will be convert to RHI ASAP)(Vulkan/D3D11 WIP)
- **ECS system**: component based GameObject and data driven programming
- **reflection system && simple editor**: reflect components fields for editing, with `imgui` as a simple editor
- **glb/gltf model loading**: load customized models

### Current Planning 
- **cluster forward lighting**: transmit lighting based on screen location
- **Advanced Anti-Aliasing**: MSAA, FXAA. TXAA support WIP. 
- **PBR Material System**: Physically based rendering WIP
- **Flexible Rendering Pipelines**: Choose between deferred, forward, and traditional rendering.
- **Ambient Occlusion Techniques**: SSAO, HBAO+ and others (WIP)
- **Multi-Rendering Backends**: Currently supports OpenGL. DirectX11/12, and Vulkan WIP.

### Future Roadmap
- Add rendering abstraction Layer
- Use Fast-Delegation to lower callback function costs
- Add Irrklang as audio engine
- Add Lua scripting binding 
- Bullet physics engine integration
- ParticleFX particle system
- Animation engine integration

## Project Structure 
- `resources` : contains all assets, such as models, textures, audio, animations, CGs, etc.
Noticed that this directory is not sync up. You are encouraged to use your own assets.

- `Sources` : contains all actual code. `Engine` is the armada engine itself, `Examples` are some demo & tests to show how to use the engine. `Thirdparty` contains some of the external library.

## Cross-platform Build
This engine is both compiled and run cross-platform. It relys on `cmake` to find dependencies and build for each platform.
If you want play the demo, or use this engine to develop, you can:
1. download the pre-built binaries from the Github Action CI build or
2. build locally
### 1: Github Action CI build
[![CMake on multiple platforms](https://github.com/Ampher-4/armada-engine-prototype/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=scorching)](https://github.com/Ampher-4/armada-engine-prototype/actions/workflows/cmake-multi-platform.yml)

you can go go the action page to download build executables on desired platform.
### 2: local build
for linux, you can run `dependency.sh` to install all dependencies.
for windows, you can use `vcpkg` to install all dependencies using `vcpkg.json` under manifest mode.
After generating the cache, you would found multiple Cmake build targets, with each one has clear explainations.
