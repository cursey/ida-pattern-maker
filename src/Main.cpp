#include <idp.hpp>
#include <loader.hpp>

#include "Plugin.hpp"

// Plugin interface to IDA.
plugin_t PLUGIN {
    IDP_INTERFACE_VERSION,
    g_plugin.Flags,
    []() { return g_plugin.initialize(); },
    []() { return g_plugin.terminate(); },
    [](size_t arg) { return g_plugin.run(arg); },
    g_plugin.Comment,
    g_plugin.Help,
    g_plugin.Name,
    g_plugin.Hotkey
};
