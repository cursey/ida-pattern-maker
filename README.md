# IDA Pattern Maker
A simple plugin that lets you generate patterns for code in IDA 7.00. 


## Usage
1) Drag `PatternMaker.dll` and `PatternMaker64.dll` into your IDA plugins folder
2) Run the plugin (hotkey is Ctrl+Alt+S by default) while the cursor is on an instruction
3) Thats it, output will be in the console

## Build Requirements
* IDA 7.00 SDK (put `idasdk70` in the project folder)
* Visual Studio (cmake projects are currently pretty specific to VS)
* CMake
