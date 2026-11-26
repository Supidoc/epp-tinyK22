# tinyK22
Project for the tinyK22 in module EPP.
You can use this project as a DevContainer (with Docker) or natively.

In native mode, make sure you call the 'setenv' script file prior launching VS Code to configure the environment.
As the script file is specific for your environment: make sure you check and update the content.

## Build
Project has `debug` and `release` targets, using CMake Presets. 

Configure:
```
cmake --list-presets
cmake --preset debug
cmake --preset debug --fresh
cmake --preset release
```

Build:
```
cmake --build --list-presets
cmake --build --preset debug
cmake --build --preset debug --target clean
cmake --build --preset release
```
