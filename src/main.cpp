#include "main.hpp"
#include "scotland2/shared/modloader.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-utils.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

bool flyEnabled = false;
bool noclipEnabled = false;
bool speedEnabled = false;
bool highJumpEnabled = false;

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

// Hook the main update loop
MAKE_HOOK_FIND_CLASS_UNSAFE_STATIC(SceneManager_LoadScene, "UnityEngine.SceneManagement", "SceneManager", "LoadScene", void, StringW sceneName) {
    PaperLogger.info("Scene loading: {}", static_cast<std::string>(sceneName));
    SceneManager_LoadScene(sceneName);
}

MOD_EXTERN_FUNC void setup(CModInfo* info) noexcept {
    *info = modInfo.to_c();
    getConfig().Load();
    Paper::Logger::RegisterFileContextId(PaperLogger.tag);
    PaperLogger.info("Baboon Mod Menu v1.0.0 loaded!");
}

MOD_EXTERN_FUNC void late_load() noexcept {
    il2cpp_functions::Init();
    PaperLogger.info("Installing hooks...");
    INSTALL_HOOK(PaperLogger, SceneManager_LoadScene);
    PaperLogger.info("All hooks installed!");
}
