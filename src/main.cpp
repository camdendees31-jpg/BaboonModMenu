#include "main.hpp"
#include "scotland2/shared/modloader.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

bool flyEnabled = false;
bool speedEnabled = false;
bool noclipEnabled = false;
bool highJumpEnabled = false;

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

MOD_EXTERN_FUNC void setup(CModInfo* info) noexcept {
    *info = modInfo.to_c();
    getConfig().Load();
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);
    PaperLogger.info("Baboon Mod Menu loaded!");
}

MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();
    PaperLogger.info("Installing hooks...");
    PaperLogger.info("All hooks installed!");
}
