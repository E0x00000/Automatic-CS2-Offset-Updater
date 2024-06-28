#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include <Windows.h>
#include <optional>
#include <optional>
#include <string>
#include <iostream>
#include <windows.h> // Para o tipo DWORD
using namespace std;




using json = nlohmann::json;
#include <cpr/cpr.h>
json loadJsonFromResponse(const std::string& url) 
{
    auto response = cpr::Get(cpr::Url{ url });

    if (response.status_code == 200) {
        std::string json_content = response.text;
        try {
            json j = json::parse(json_content);
            return j;
        }
        catch (const json::parse_error& e) {
            throw;
        }
    }
    else {
        throw std::runtime_error("Erro ao baixar JSON");
    }
}


std::string findValueByName(const json& j, const std::string& structName, const std::string& name) {
    if (j.contains(structName) && j[structName].is_array()) {
        for (const auto& constant : j[structName]) {
            if (constant.contains("name") && constant["name"] == name &&
                constant.contains("value")) {
                std::string valueStr = constant["value"];
                return valueStr;
            }
        }
    }
    return "";
}


namespace Offset {
    

    struct GeneralOffsets
    {
        string EntityList;
        string Matrix;
        string ViewAngle;
        string LocalPlayerController;
        string LocalPlayerPawn;
        string GlobalVars;
        string InventoryServices;
        string PlantedC4;
        string InputSystem;
        string Sensitivity;
        string Pointer;
        string dwWindowHeight;
        string dwWindowWidth;
    } General;

    struct EntityOffsets {
        string m_bPawnIsAlive;
        string m_hPlayerPawn;
        string m_iszPlayerName;
        string m_flGravityScale;
    } Entity;

    struct PawnOffsets {
        string m_pMovementServices;//
        string m_pWeaponServices;//
        string m_pBulletServices;//
        string m_pCameraServices;//
        string m_pViewModelServices;//
        string m_pClippingWeapon;//
        string m_hViewModel;
        string m_nCrouchState;
        string m_bIsScoped;
        string m_bIsDefusing;
        string m_totalHitsOnServer;
        string m_vOldOrigin;
        string m_ArmorValue;
        string m_iMaxHealth;
        string m_iHealth;
        string m_pGameSceneNode;
        string m_modelState;
        string m_vecOrigin;
        string m_hOwnerEntity;
        string m_angEyeAngles;
        string m_vecLastClipCameraPos;
        string m_iShotsFired;
        string m_flFlashMaxAlpha;
        string m_flFlashDuration;
        string m_aimPunchAngle;
        string m_aimPunchCache;
        string m_iIDEntIndex;
        string m_iTeamNum;
        string m_iDesiredFOV;
        string m_iFOVStart;
        string m_entitySpottedState;
        string m_bSpottedByMask;
        string m_vecAbsVelocity;
        string m_bIsBuyMenuOpen;
    } Pawn;

    struct GlobalVarOffsets {
        string RealTime;
        string FrameCount;
        string MaxClients;
        string IntervalPerTick;
        string CurrentTime;
        string CurrentTime2;
        string TickCount;
        string IntervalPerTick2;
        string CurrentNetchan;
        string CurrentMap;
        string CurrentMapName;
    } GlobalVar;

    struct PlayerControllerOffsets {
        string m_hPawn;
        string m_pObserverServices;
        string m_hObserverTarget;
        string m_hController;
        string m_iPawnArmor;
        string m_bPawnHasDefuser;
        string m_bPawnHasHelmet;
    } PlayerController;

    struct EconEntityOffsets {
        string m_AttributeManager;
        string m_nFallbackPaintKit;
        string m_nFallbackSeed;
        string m_flFallbackWear;
        string m_nFallbackStatTrak;
        string m_szCustomName;
        string m_iEntityQuality;
        string m_iItemIDHigh;
    } EconEntity;

    struct WeaponBaseOffsets {
        string WeaponDataPTR;
        string szName;
        string Clip1;
        string m_iMaxClip1;
        string m_flCycleTime;
        string m_flPenetration;
        string m_WeaponType;
        string m_flInaccuracyMove;
        string m_bInReload;
        string WeaponSize;
        string m_hActiveWeapon;
        string m_Item;
        string m_iItemDefinitionIndex;
        string m_MeshGroupMask;
    } WeaponBase;

    struct C4Offsets {
        string m_bBeingDefused;
        string m_flDefuseCountDown;
        string m_nBombSite;
    } C4;

    struct InGameMoneyServicesOffsets {
        string m_pInGameMoneyServices;
        string m_iAccount;
        string m_iTotalCashSpent;
        string m_iCashSpentThisRound;
    } InGameMoneyServices;

    struct SmokeGrenadeProjectileOffsets {
        string m_nSmokeEffectTickBegin;
        string m_bDidSmokeEffect;
        string m_nRandomSeed;
        string m_vSmokeColor;
        string m_vSmokeDetonationPos;
        string m_VoxelFrameData;
        string m_bSmokeVolumeDataReceived;
        string m_bSmokeEffectSpawned;
    } SmokeGrenadeProjectile;
}
int main() {

    std::string url = "https://raw.githubusercontent.com/E0x00000/CS2-Basic-Dump/main/output%20updater/client_dll.json";

    try {
        json j = loadJsonFromResponse(url);
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
        Offset::Pawn.m_entitySpottedState = findValueByName(j, "PawnOffsets", "m_entitySpottedState");
        Offset::Pawn.m_pWeaponServices = findValueByName(j, "PawnOffsets", "m_pWeaponServices");
        Offset::Pawn.m_pCameraServices = findValueByName(j, "PawnOffsets", "m_pCameraServices");
        Offset::Pawn.m_pMovementServices = findValueByName(j, "PawnOffsets", "m_pMovementServices");
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
        Offset::Pawn.m_vecOrigin = findValueByName(j, "PawnOffsets", "m_vecOrigin");
        Offset::Pawn.m_entitySpottedState = findValueByName(j, "PawnOffsets", "m_entitySpottedState");
        Offset::Pawn.m_entitySpottedState = findValueByName(j, "PawnOffsets", "m_entitySpottedState");
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
        Offset::EconEntity.m_AttributeManager = findValueByName(j, "EconEntityOffsets", "m_AttributeManager");
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
        Offset::SmokeGrenadeProjectile.m_vSmokeColor = findValueByName(j, "SmokeGrenadeProjectileOffsets", "m_vSmokeColor");
        Offset::General.dwEntityList = findValueByName(j, "GeneralOffsets", "dwEntityList");
        Offset::General.dwGlobalVars = findValueByName(j, "GeneralOffsets", "dwGlobalVars");
        Offset::General.dwLocalPlayerController = findValueByName(j, "GeneralOffsets", "dwLocalPlayerController");
        Offset::General.dwLocalPlayerPawn = findValueByName(j, "GeneralOffsets", "dwLocalPlayerPawn");
        Offset::General.dwPlantedC4 = findValueByName(j, "GeneralOffsets", "dwPlantedC4");
        Offset::General.dwViewAngles = findValueByName(j, "GeneralOffsets", "dwViewAngles");
        Offset::General.dwWindowHeight = findValueByName(j, "GeneralOffsets", "dwWindowHeight");
        Offset::General.dwWindowWidth = findValueByName(j, "GeneralOffsets", "dwWindowWidth");
        Offset::General.jump = findValueByName(j, "GeneralOffsets", "jump");




    }
    catch (const std::exception& e) 
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    

    std::cout << Offset::Entity.m_bPawnIsAlive << std::endl;

    return 0;
}