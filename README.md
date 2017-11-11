# IDA Pattern Maker
A simple plugin that lets you generate patterns for code in IDA 7.00. 


## Usage
1) Drag `PatternMaker.dll` and `PatternMaker64.dll` into your IDA plugins folder
2) Run the plugin (hotkey is Ctrl+Alt+S by default) while the cursor is on an instruction
3) Thats it, output will be in the console

## Usage Requirements
If you're using the precompiled binaries then you will need the __Microsoft Visual C++ Redistributable for Visual Studio 2017__ located near the bottom of [this page](https://www.visualstudio.com/downloads/).

## Build Requirements
* IDA 7.00 SDK 
* Visual Studio (cmake projects are currently pretty specific to VS)
* CMake

Note: `PatternMaker64.dll` will only build properly if you've renamed the 64 bit target `ida.lib` (the one for `__EA64__`) to `ida64.lib`.
