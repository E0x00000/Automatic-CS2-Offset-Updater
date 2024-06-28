#include <iostream>
#include <fstream>
#include <vector>
#include "json.hpp"
#include <Windows.h>

using json = nlohmann::json;
struct Constant {
    std::string name;
    int value;
};

struct Namespace {
    std::string name;
    std::vector<Constant> constants;
};

namespace Offset {
    inline DWORD EntityList;
    inline DWORD Matrix;
    inline DWORD ViewAngle;
    inline DWORD LocalPlayerController;
    inline DWORD LocalPlayerPawn;
    inline DWORD GlobalVars;
    inline DWORD InventoryServices;
    inline DWORD PlantedC4;
    inline DWORD InputSystem;
    inline DWORD Sensitivity;
    inline DWORD Pointer;
    inline DWORD dwWindowHeight;
    inline DWORD dwWindowWidth;

    struct EntityOffsets {
        DWORD IsAlive;
        DWORD PlayerPawn;
        DWORD iszPlayerName;
        DWORD GravityScale;
    } Entity;

    struct PawnOffsets {
        DWORD MovementServices;
        DWORD WeaponServices;
        DWORD BulletServices;
        DWORD CameraServices;
        DWORD ViewModelServices;
        DWORD pClippingWeapon;
        DWORD ViewModel;
        DWORD CrouchState;
        DWORD isScoped;
        DWORD isDefusing;
        DWORD TotalHit;
        DWORD Pos;
        DWORD CurrentArmor;
        DWORD MaxHealth;
        DWORD CurrentHealth;
        DWORD GameSceneNode;
        DWORD BoneArray;
        DWORD m_vecOrigin;
        DWORD m_hOwnerEntity;
        DWORD angEyeAngles;
        DWORD vecLastClipCameraPos;
        DWORD iShotsFired;
        DWORD flFlashMaxAlpha;
        DWORD flFlashDuration;
        DWORD aimPunchAngle;
        DWORD aimPunchCache;
        DWORD iIDEntIndex;
        DWORD iTeamNum;
        DWORD DesiredFov;
        DWORD iFovStart;
        DWORD fFlags;
        DWORD bSpottedByMask;
        DWORD AbsVelocity;
        DWORD IsBuying;
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
        DWORD PawnArmor;
        DWORD HasDefuser;
        DWORD HasHelmet;
    } PlayerController;

    struct EconEntityOffsets {
        DWORD AttributeManager;
        DWORD FallbackPaintKit;
        DWORD FallbackSeed;
        DWORD FallbackWear;
        DWORD FallbackStatTrak;
        DWORD szCustomName;
        DWORD EntityQuality;
        DWORD ItemIDHigh;
    } EconEntity;

    struct WeaponBaseOffsets {
        DWORD WeaponDataPTR;
        DWORD szName;
        DWORD Clip1;
        DWORD MaxClip;
        DWORD CycleTime;
        DWORD Penetration;
        DWORD WeaponType;
        DWORD Inaccuracy;
        DWORD inReload;
        DWORD WeaponSize;
        DWORD ActiveWeapon;
        DWORD Item;
        DWORD ItemDefinitionIndex;
        DWORD m_MeshGroupMask;
    } WeaponBase;

    struct C4Offsets {
        DWORD m_bBeingDefused;
        DWORD m_flDefuseCountDown;
        DWORD m_nBombSite;
    } C4;

    struct InGameMoneyServicesOffsets {
        DWORD MoneyServices;
        DWORD Account;
        DWORD TotalCashSpent;
        DWORD CashSpentThisRound;
    } InGameMoneyServices;

    struct SmokeGrenadeProjectileOffsets {
        DWORD nSmokeEffectTickBegin;
        DWORD bDidSmokeEffect;
        DWORD nRandomSeed;
        DWORD vSmokeColor;
        DWORD vSmokeDetonationPos;
        DWORD VoxelFrameData;
        DWORD bSmokeVolumeDataReceived;
        uintptr_t bSmokeEffectSpawned;
    } SmokeGrenadeProjectile;

    bool UpdateOffsets() {
        return true;
    }
}

int findConstantValue(const std::vector<Namespace>& namespaces, const std::string& variableName) {
    for (const auto& ns : namespaces) {
        for (const auto& constant : ns.constants) {
            if (constant.name == variableName) {
                return constant.value;
            }
        }
    }
    return -1;
}

void runCheat(const std::vector<Namespace>& namespaces) {
    
    for (const auto& ns : namespaces) {
        std::cout << "Namespace: " << ns.name << std::endl;

        
        for (const auto& constant : ns.constants) {
            std::cout << "    " << constant.name << ": " << constant.value << std::endl;
        }
    }
}

int main() {
    
    std::ifstream file("C:\\Users\\miss\\Downloads\\dumper\\output\\teste.json");
    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo JSON." << std::endl;
        return 1;
    }

    json j;
    try {
        file >> j;
    }
    catch (const std::exception& e) {
        std::cerr << "Erro ao fazer parse do JSON: " << e.what() << std::endl;
        return 1;
    }

    std::vector<Namespace> namespaces;

    for (auto& obj : j) {
        Namespace ns;
        ns.name = obj["name"];
        if (obj.find("constants") != obj.end()) {
            for (auto& constant : obj["constants"]) {
                Constant c;
                c.name = constant["name"];
                c.value = constant["value"];
                ns.constants.push_back(c);
            }
        }

        namespaces.push_back(ns);
    }

    runCheat(namespaces);

    return 0;
}