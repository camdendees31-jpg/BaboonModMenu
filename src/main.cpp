#include "main.hpp"
#include "scotland2/shared/modloader.h"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Rigidbody.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// --- Mod toggles ---
bool flyEnabled = false;
bool noclipEnabled = false;
bool speedEnabled = false;
bool highJumpEnabled = false;
bool godModeEnabled = false;
float flySpeed = 5.0f;
float speedMult = 2.0f;

Configuration& getConfig() {
    static Configuration config(modInfo);
    return config;
}

MAKE_HOOK_MATCH(Rigidbody_FixedUpdate,
    &UnityEngine::Rigidbody::Sleep, void,
    UnityEngine::Rigidbody* self) {

    Rigidbody_FixedUpdate(self);

    if (flyEnabled) {
        self->set_useGravity(false);
        auto vel = self->get_velocity();
        vel.y = flySpeed;
        self->set_velocity(vel);
    } else {
        self->set_useGravity(true);
    }
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
    INSTALL_HOOK(PaperLogger, Rigidbody_FixedUpdate);
    PaperLogger.info("All hooks installed!");
}