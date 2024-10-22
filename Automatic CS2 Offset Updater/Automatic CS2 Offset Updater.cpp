#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include <Windows.h>
#include <optional>
#include <optional>
#include <string>
#include <iostream>
#include <windows.h>
using namespace std;
using json = nlohmann::json;
#include <cpr/cpr.h>

namespace Offset {


    struct GeneralOffsets
    {
       DWORD dwEntityList;
       DWORD dwGlobalVars;
       DWORD dwLocalPlayerController;
       DWORD dwLocalPlayerPawn;
       DWORD LocalPlayerPawn;
       DWORD dwPlantedC4;
       DWORD dwViewAngles;
       DWORD PlantedC4;
       DWORD InputSystem;
       DWORD Sensitivity;
       DWORD dwViewMatrix;
       DWORD dwWindowHeight;
       DWORD dwWindowWidth;
    } General;

    struct EntityOffsets {
        DWORD m_bPawnIsAlive;
        DWORD m_hPlayerPawn;
        DWORD m_iszPlayerName;
        DWORD m_flGravityScale;
    } Entity;

    struct PawnOffsets {
        DWORD m_pMovementServices;//
        DWORD m_pWeaponServices;//
        DWORD m_pBulletServices;//
        DWORD m_pCameraServices;//
        DWORD m_pViewModelServices;//
        DWORD m_pClippingWeapon;//
        DWORD m_hViewModel;
        DWORD m_nCrouchState;
        DWORD m_bIsScoped;
        DWORD m_bIsDefusing;
        DWORD m_totalHitsOnServer;
        DWORD m_vOldOrigin;
        DWORD m_ArmorValue;
        DWORD m_iMaxHealth;
        DWORD m_iHealth;
        DWORD m_pGameSceneNode;
        DWORD m_modelState;
        DWORD m_vecOrigin;
        DWORD m_hOwnerEntity;
        DWORD m_angEyeAngles;
        DWORD m_vecLastClipCameraPos;
        DWORD m_iShotsFired;
        DWORD m_flFlashMaxAlpha;
        DWORD m_flFlashDuration;
        DWORD m_aimPunchAngle;
        DWORD m_aimPunchCache;
        DWORD m_iIDEntIndex;
        DWORD m_iTeamNum;
        DWORD m_iDesiredFOV;
        DWORD m_iFOVStart;
        DWORD m_entitySpottedState;
        DWORD m_bSpottedByMask;
        DWORD m_vecAbsVelocity;
        DWORD m_bIsBuyMenuOpen;
    } Pawn;

    struct GlobalVarOffsets {
        DWORD RealTime;
        DWORD FrameCount;
        DWORD MaxClients;
        DWORD IntervalPerTick;
        DWORD CurrentTime;
        DWORD CurrentTime2;
        DWORD TickCount;
        DWORD IntervalPerTick2;
        DWORD CurrentNetchan;
        DWORD CurrentMap;
        DWORD CurrentMapName;
    } GlobalVar;

    struct PlayerControllerOffsets {
        DWORD m_hPawn;
        DWORD m_pObserverServices;
        DWORD m_hObserverTarget;
        DWORD m_hController;
        DWORD m_iPawnArmor;
        DWORD m_bPawnHasDefuser;
        DWORD m_bPawnHasHelmet;
    } PlayerController;

    struct EconEntityOffsets {
        DWORD m_AttributeManager;
        DWORD m_nFallbackPaintKit;
        DWORD m_nFallbackSeed;
        DWORD m_flFallbackWear;
        DWORD m_nFallbackStatTrak;
        DWORD m_szCustomName;
        DWORD m_iEntityQuality;
        DWORD m_iItemIDHigh;
    } EconEntity;

    struct WeaponBaseOffsets {
        DWORD WeaponDataPTR;
        DWORD szName;
        DWORD Clip1;
        DWORD m_iMaxClip1;
        DWORD m_flCycleTime;
        DWORD m_flPenetration;
        DWORD m_WeaponType;
        DWORD m_flInaccuracyMove;
        DWORD m_bInReload;
        DWORD WeaponSize;
        DWORD m_hActiveWeapon;
        DWORD m_Item;
        DWORD m_iItemDefinitionIndex;
        DWORD m_MeshGroupMask;
    } WeaponBase;

    struct C4Offsets {
        DWORD m_bBeingDefused;
        DWORD m_flDefuseCountDown;
        DWORD m_nBombSite;
    } C4;

    struct InGameMoneyServicesOffsets {
        DWORD m_pInGameMoneyServices;
        DWORD m_iAccount;
        DWORD m_iTotalCashSpent;
        DWORD m_iCashSpentThisRound;
    } InGameMoneyServices;

    struct SmokeGrenadeProjectileOffsets {
        DWORD m_nSmokeEffectTickBegin;
        DWORD m_bDidSmokeEffect;
        DWORD m_nRandomSeed;
        DWORD m_vSmokeColor;
        DWORD m_vSmokeDetonationPos;
        DWORD m_VoxelFrameData;
        DWORD m_bSmokeVolumeDataReceived;
        DWORD m_bSmokeEffectSpawned;
    } SmokeGrenadeProjectile;
}
using DWORD = unsigned long;

DWORD findValueByName(const nlohmann::json& j, const std::string& category, const std::string& name) {
    if (j.contains(category) && j[category].contains("constants")) {
        for (const auto& constant : j[category]["constants"]) {
            if (constant["name"] == name) {
                return std::stoul(constant["value"].get<std::string>(), nullptr, 0);
            }
        }
    }
    throw std::runtime_error("Constante " + name + " n�o encontrada em " + category);
}


void parseAndAssignConstants(const std::string& jsonString) {
    json j = json::parse(jsonString);
    Offset::General.dwEntityList = findValueByName(j, "GeneralOffsets", "dwEntityList");
    Offset::General.dwGlobalVars = findValueByName(j, "GeneralOffsets", "dwGlobalVars");
    Offset::General.dwLocalPlayerController = findValueByName(j, "GeneralOffsets", "dwLocalPlayerController");
    Offset::General.dwLocalPlayerPawn = findValueByName(j, "GeneralOffsets", "dwLocalPlayerPawn");
    Offset::General.dwPlantedC4 = findValueByName(j, "GeneralOffsets", "dwPlantedC4");
    Offset::General.dwViewAngles = findValueByName(j, "GeneralOffsets", "dwViewAngles");
    Offset::General.dwWindowHeight = findValueByName(j, "GeneralOffsets", "dwWindowHeight");
    Offset::General.dwWindowWidth = findValueByName(j, "GeneralOffsets", "dwWindowWidth");

    Offset::Entity.m_iszPlayerName = findValueByName(j, "EntityOffsets", "m_iszPlayerName");
    Offset::Entity.m_flGravityScale = findValueByName(j, "EntityOffsets", "m_flGravityScale");
    Offset::Entity.m_hPlayerPawn = findValueByName(j, "EntityOffsets", "m_hPlayerPawn");
    Offset::Entity.m_bPawnIsAlive = findValueByName(j, "EntityOffsets", "m_bPawnIsAlive");

    Offset::Pawn.m_modelState = findValueByName(j, "PawnOffsets", "m_modelState");
    Offset::Pawn.m_pBulletServices = findValueByName(j, "PawnOffsets", "m_pBulletServices");
    Offset::Pawn.m_aimPunchAngle = findValueByName(j, "PawnOffsets", "m_aimPunchAngle");
    Offset::Pawn.m_aimPunchCache = findValueByName(j, "PawnOffsets", "m_aimPunchCache");
    Offset::Pawn.m_bIsBuyMenuOpen = findValueByName(j, "PawnOffsets", "m_bIsBuyMenuOpen");
    Offset::Pawn.m_entitySpottedState = findValueByName(j, "PawnOffsets", "m_entitySpottedState");
    Offset::Pawn.m_bIsScoped = findValueByName(j, "PawnOffsets", "m_bIsScoped");
    Offset::Pawn.m_bIsDefusing = findValueByName(j, "PawnOffsets", "m_bIsDefusing");
    Offset::Pawn.m_iShotsFired = findValueByName(j, "PawnOffsets", "m_iShotsFired");
    Offset::Pawn.m_ArmorValue = findValueByName(j, "PawnOffsets", "m_ArmorValue");
    Offset::Pawn.m_hViewModel = findValueByName(j, "PawnOffsets", "m_hViewModel");
    Offset::Pawn.m_nCrouchState = findValueByName(j, "PawnOffsets", "m_nCrouchState");
    Offset::Pawn.m_iFOVStart = findValueByName(j, "PawnOffsets", "m_iFOVStart");
    Offset::Pawn.m_pViewModelServices = findValueByName(j, "PawnOffsets", "m_pViewModelServices");
    Offset::Pawn.m_vecLastClipCameraPos = findValueByName(j, "PawnOffsets", "m_vecLastClipCameraPos");
    Offset::Pawn.m_pClippingWeapon = findValueByName(j, "PawnOffsets", "m_pClippingWeapon");
    Offset::Pawn.m_flFlashMaxAlpha = findValueByName(j, "PawnOffsets", "m_flFlashMaxAlpha");
    Offset::Pawn.m_flFlashDuration = findValueByName(j, "PawnOffsets", "m_flFlashDuration");
    Offset::Pawn.m_angEyeAngles = findValueByName(j, "PawnOffsets", "m_angEyeAngles");
    Offset::Pawn.m_iIDEntIndex = findValueByName(j, "PawnOffsets", "m_iIDEntIndex");
    Offset::Pawn.m_iDesiredFOV = findValueByName(j, "PawnOffsets", "m_iDesiredFOV");
    Offset::Pawn.m_vOldOrigin = findValueByName(j, "PawnOffsets", "m_vOldOrigin");
    Offset::Pawn.m_bSpottedByMask = findValueByName(j, "PawnOffsets", "m_bSpottedByMask");
    Offset::Pawn.m_totalHitsOnServer = findValueByName(j, "PawnOffsets", "m_totalHitsOnServer");
    Offset::Pawn.m_vecOrigin = findValueByName(j, "PawnOffsets", "m_vecOrigin");
    Offset::Pawn.m_pGameSceneNode = findValueByName(j, "PawnOffsets", "m_pGameSceneNode");
    Offset::Pawn.m_iMaxHealth = findValueByName(j, "PawnOffsets", "m_iMaxHealth");
    Offset::Pawn.m_iHealth = findValueByName(j, "PawnOffsets", "m_iHealth");
    Offset::Pawn.m_iTeamNum = findValueByName(j, "PawnOffsets", "m_iTeamNum");
    Offset::Pawn.m_vecAbsVelocity = findValueByName(j, "PawnOffsets", "m_vecAbsVelocity");
    Offset::Pawn.m_hOwnerEntity = findValueByName(j, "PawnOffsets", "m_hOwnerEntity");

    Offset::PlayerController.m_hPawn = findValueByName(j, "PlayerControllerOffsets", "m_hPawn");
    Offset::PlayerController.m_pObserverServices = findValueByName(j, "PlayerControllerOffsets", "m_pObserverServices");
    Offset::PlayerController.m_hController = findValueByName(j, "PlayerControllerOffsets", "m_hController");
    Offset::PlayerController.m_hObserverTarget = findValueByName(j, "PlayerControllerOffsets", "m_hObserverTarget");
    Offset::PlayerController.m_iPawnArmor = findValueByName(j, "PlayerControllerOffsets", "m_iPawnArmor");
    Offset::PlayerController.m_bPawnHasDefuser = findValueByName(j, "PlayerControllerOffsets", "m_bPawnHasDefuser");
    Offset::PlayerController.m_bPawnHasHelmet = findValueByName(j, "PlayerControllerOffsets", "m_bPawnHasHelmet");

    Offset::EconEntity.m_AttributeManager = findValueByName(j, "EconEntityOffsets", "m_AttributeManager");
    Offset::EconEntity.m_nFallbackPaintKit = findValueByName(j, "EconEntityOffsets", "m_nFallbackPaintKit");
    Offset::EconEntity.m_nFallbackSeed = findValueByName(j, "EconEntityOffsets", "m_nFallbackSeed");
    Offset::EconEntity.m_flFallbackWear = findValueByName(j, "EconEntityOffsets", "m_flFallbackWear");
    Offset::EconEntity.m_nFallbackStatTrak = findValueByName(j, "EconEntityOffsets", "m_nFallbackStatTrak");
    Offset::EconEntity.m_iEntityQuality = findValueByName(j, "EconEntityOffsets", "m_iEntityQuality");
    Offset::EconEntity.m_iItemIDHigh = findValueByName(j, "EconEntityOffsets", "m_iItemIDHigh");
    Offset::EconEntity.m_szCustomName = findValueByName(j, "EconEntityOffsets", "m_szCustomName");

    Offset::WeaponBase.m_Item = findValueByName(j, "WeaponBaseOffsets", "m_Item");
    Offset::WeaponBase.m_iMaxClip1 = findValueByName(j, "WeaponBaseOffsets", "m_iMaxClip1");
    Offset::WeaponBase.m_MeshGroupMask = findValueByName(j, "WeaponBaseOffsets", "m_MeshGroupMask");
    Offset::WeaponBase.m_iItemDefinitionIndex = findValueByName(j, "WeaponBaseOffsets", "m_iItemDefinitionIndex");
    Offset::WeaponBase.m_hActiveWeapon = findValueByName(j, "WeaponBaseOffsets", "m_hActiveWeapon");
    Offset::WeaponBase.m_bInReload = findValueByName(j, "WeaponBaseOffsets", "m_bInReload");
    Offset::WeaponBase.m_WeaponType = findValueByName(j, "WeaponBaseOffsets", "m_WeaponType");
    Offset::WeaponBase.m_flCycleTime = findValueByName(j, "WeaponBaseOffsets", "m_flCycleTime");
    Offset::WeaponBase.m_flInaccuracyMove = findValueByName(j, "WeaponBaseOffsets", "m_flInaccuracyMove");
    Offset::WeaponBase.m_flPenetration = findValueByName(j, "WeaponBaseOffsets", "m_flPenetration");

    Offset::C4.m_nBombSite = findValueByName(j, "C4Offsets", "m_nBombSite");
    Offset::C4.m_bBeingDefused = findValueByName(j, "C4Offsets", "m_bBeingDefused");
    Offset::C4.m_flDefuseCountDown = findValueByName(j, "C4Offsets", "m_flDefuseCountDown");

    Offset::InGameMoneyServices.m_iAccount = findValueByName(j, "InGameMoneyServicesOffsets", "m_iAccount");
    Offset::InGameMoneyServices.m_iTotalCashSpent = findValueByName(j, "InGameMoneyServicesOffsets", "m_iTotalCashSpent");
    Offset::InGameMoneyServices.m_iCashSpentThisRound = findValueByName(j, "InGameMoneyServicesOffsets", "m_iCashSpentThisRound");
    Offset::InGameMoneyServices.m_pInGameMoneyServices = findValueByName(j, "InGameMoneyServicesOffsets", "m_pInGameMoneyServices");

    Offset::SmokeGrenadeProjectile.m_nSmokeEffectTickBegin = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_nSmokeEffectTickBegin");
    Offset::SmokeGrenadeProjectile.m_bDidSmokeEffect = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_bDidSmokeEffect");
    Offset::SmokeGrenadeProjectile.m_nRandomSeed = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_nRandomSeed");
    Offset::SmokeGrenadeProjectile.m_vSmokeColor = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_vSmokeColor");
    Offset::SmokeGrenadeProjectile.m_vSmokeDetonationPos = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_vSmokeDetonationPos");
    Offset::SmokeGrenadeProjectile.m_VoxelFrameData = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_VoxelFrameData");
    Offset::SmokeGrenadeProjectile.m_bSmokeVolumeDataReceived = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_bSmokeVolumeDataReceived");
    Offset::SmokeGrenadeProjectile.m_bSmokeEffectSpawned = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_bSmokeEffectSpawned");
    Offset::General.dwEntityList = findValueByName(j, "GeneralOffsets", "dwEntityList");
    Offset::General.dwGlobalVars = findValueByName(j, "GeneralOffsets", "dwGlobalVars");
    Offset::General.dwLocalPlayerController = findValueByName(j, "GeneralOffsets", "dwLocalPlayerController");
    Offset::General.dwLocalPlayerPawn = findValueByName(j, "GeneralOffsets", "dwLocalPlayerPawn");
    Offset::General.dwPlantedC4 = findValueByName(j, "GeneralOffsets", "dwPlantedC4");
    Offset::General.dwViewAngles = findValueByName(j, "GeneralOffsets", "dwViewAngles");
    Offset::General.dwWindowHeight = findValueByName(j, "GeneralOffsets", "dwWindowHeight");
    Offset::General.dwWindowWidth = findValueByName(j, "GeneralOffsets", "dwWindowWidth");
    Offset::General.dwViewMatrix = findValueByName(j, "GeneralOffsets", "dwViewMatrix");
}






int main() {
    try {
        std::string url = "https://raw.githubusercontent.com/E0x00000/CS2-Basic-Dump/main/final%20dump.json";
        cpr::Response r = cpr::Get(cpr::Url{ url });
        parseAndAssignConstants(r.text);
        std::cout << "dwEntityList: " << Offset::General.dwEntityList << std::endl;
        std::cout << "dwEntityList: " << Offset::General.dwViewMatrix << std::endl;
        std::cout << "m_iszPlayerName: " << Offset::Entity.m_iszPlayerName << std::endl;
        std::cout << "m_modelState: " << Offset::Pawn.m_modelState << std::endl;
        std::cout << "m_hPawn: " << Offset::PlayerController.m_hPawn << std::endl;
        std::cout << "m_AttributeManager: " << Offset::EconEntity.m_AttributeManager << std::endl;
        std::cout << "m_Item: " << Offset::WeaponBase.m_Item << std::endl;
        std::cout << "m_nBombSite: " << Offset::C4.m_nBombSite << std::endl;
        std::cout << "m_iAccount: " << Offset::InGameMoneyServices.m_iAccount << std::endl;
        std::cout << "m_nSmokeEffectTickBegin: " << Offset::SmokeGrenadeProjectile.m_nSmokeEffectTickBegin << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}