# Armada Engine

A modern game engine focused on AAA FPS/TPS game development.

## Overview & Introductions
Armada Engine (fleet engine) is a personal project aimed at building a high-performance game engine tailored for AAA first-person and third-person shooter titles.

### Current Features
- **Modern C++ Foundation**: Built with C++20 and later standards
- **Multi-Rendering Backends**: Supports OpenGL, DirectX, and Vulkan
- **Flexible Rendering Pipelines**: Choose between deferred, forward, and traditional rendering
- **Cross-Platform Support**: Compiles and runs on Linux and Windows. (BSD support is exprimental)
- **Advanced Anti-Aliasing**: Implementing SSAA, TXAA, MSAA, DLAA, and more
- **Ambient Occlusion Techniques**: Implementing HBAO+, RTAO, GTAO, and others
- **PBR Material System**: Implementing physically based rendering

### Future Roadmap
- Use Fast-Delegation to lower callback function costs
- Add Irrklang as audio engine
- Add Lua scripting binding 
- Add Entity-Component-System (ECS) architecture 
- Bullet physics engine integration
- ParticleFX particle system
- Animation engine integration

## Project Structure 
- `resources` : contains all assets, such as models, textures, audio, animations, CGs, etc.
Noticed that this directory is not sync up. You are encouraged to use your own assets.
- `shaders` : contains all shader files, including default general-purpose shaders, glsl, spirv, etc
- `sources` : contains all actual code. `engine` is the armada engine itself, `examples` are some demo & tests to show how to use the engine.

## Cross-platform Build
This engine is both compiled and run cross-platform. It relys on `cmake` to find dependencies and build for each platform.
for linux, you can run `dependency.sh` to install all dependencies.
for windows, you can use vcpkg to install all dependencies using `vcpkg.json` under manifest mode.

After generating the cache, you would found multiple build targets, with each one has clear explainations.
