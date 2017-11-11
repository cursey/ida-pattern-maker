#pragma once

#include <cstdint>
#include <vector>

class Plugin {
public:
    static constexpr int Flags = 0;
    static constexpr char* Comment = "Creates a (hopefully unique) pattern from the currently selected address. By cursey.";
    static constexpr char* Name = "Pattern Maker";
    static constexpr char* Help = "Set the cursor on an instruction you want to create a pattern for and run the plugin or press the hotkey.";
    static constexpr char* Hotkey = "Ctrl+Alt+S";

    Plugin();

    int initialize();
    bool run(size_t arg);
    void terminate();
};

extern Plugin g_plugin;
