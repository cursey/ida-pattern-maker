#include <array>
#include <algorithm>
#include <string>

#include <ida.hpp>
#include <idp.hpp>
#include <loader.hpp>

#include "Plugin.hpp"

using namespace std;

Plugin g_plugin{};

Plugin::Plugin() {
}

int Plugin::initialize() {
    return PLUGIN_OK;
}

bool Plugin::run(size_t arg) {
    msg("Pattern Maker running...\n");

    // If -1 is passed as the arg then lets unload.
    if (arg == (size_t)-1) {
        msg("Unloading Pattern Maker.\n");

        PLUGIN.flags |= PLUGIN_UNL;

        return false;
    }

    auto address = get_screen_ea();

    if (!can_decode(address)) {
        msg("Address must be the start of an instruction.\n");
        return false;
    }

    msg("Creating pattern for address: %p...\n", address);

    vector<uint8_t> bytes{};
    vector<uint8_t> mask{};
    int offset{ 0 };

    // 100 instructions max.
    for (int i = 0; i < 100; ++i) {
        // Decode the current instruction.
        insn_t instruction{};

        if (decode_insn(&instruction, address + offset) == 0) {
            msg("Failed to decode instruction @ %p!\n", address + offset);
            break;
        }

        // Add the bytes of the instruction to the bytes of our pattern.
        for (int j = 0; j < instruction.size; ++j) {
            bytes.emplace_back(get_byte(instruction.ea + j));
        }

        // By default the instruction mask is all 1's
        vector<uint8_t> instructionMask(instruction.size, 1);

        for (const auto& op : instruction.ops) {
            if (op.type == o_void) {
                break;
            }

            // If the operand isn't one of these types, fill the remaining portion
            // of the mask with 0.
            if (op.type != o_reg && op.type != o_phrase && op.type != o_displ) {
                fill(instructionMask.begin() + op.offb, instructionMask.end(), 0);
                break;
            }
        }

        // First byte is always okay, sometimes the above loop will mark an entire
        // instruction as wildcards.
        instructionMask[0] = 1;

        // Copy this isntructions mask to our pattern's mask.
        copy(instructionMask.begin(), instructionMask.end(), back_inserter(mask));

        // Search from the min-most address to the address we're making the pattern 
        // for.
        if (bin_search(inf.min_ea, address, bytes.data(), mask.data(), bytes.size(), BIN_SEARCH_FORWARD, 0) == BADADDR) {
            // Search from the address we're making the pattern for + current pattern
            // size to the max-most address.
            if (bin_search(address + bytes.size(), inf.max_ea, bytes.data(), mask.data(), bytes.size(), BIN_SEARCH_FORWARD, 0) == BADADDR) {
                msg("Unique pattern found!\n");
                break;
            }
        }

        // Continue on to the next instruction
        offset += instruction.size;
    }

    // Create a pattern from the bytes and mask.
    string pattern{};

    for (int i = 0; i < bytes.size(); ++i) {
        if (mask[i] == 1) {
            array<char, 3> byte{};

            sprintf_s(byte.data(), byte.size(), "%02X", bytes[i]);

            pattern += byte.data();
            pattern += " ";
        }
        else {
            pattern += "? ";
        }
    }

    if (!pattern.empty()) {
        pattern = pattern.substr(0, pattern.length() - 1);
        msg("Pattern: %s\n", pattern.c_str());
    }
    else {
        msg("No pattern was made!\n");
    }

    msg("Pattern Maker finished.\n");

    return true;
}

void Plugin::terminate() {
}
