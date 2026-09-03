#include "lr_entities.h"
#include <entity2/entitysystem.h>
#include <entity2/entityinstance.h>

// CS2 CEntityHandle: low 15 bits = entity index, rest = serial.
static const uint32_t kEntIndexMask = 0x7FFF;
static const uint32_t kInvalidHandle = 0xFFFFFFFF;

static CEntityInstance* ResolveHandle(uint32_t hRaw)
{
	if (hRaw == kInvalidHandle || (hRaw & kEntIndexMask) == kEntIndexMask)
		return nullptr;

	CGameEntitySystem* pES = GameEntitySystem();
	if (!pES)
		return nullptr;

	return pES->GetEntityInstance(CEntityIndex(hRaw & kEntIndexMask));
}

CCSPlayerController* CCSPlayerController::FromSlot(int iSlot)
{
	CGameEntitySystem* pES = GameEntitySystem();
	if (!pES)
		return nullptr;

	return reinterpret_cast<CCSPlayerController*>(pES->GetEntityInstance(CEntityIndex(iSlot + 1)));
}

LREntity* CCSPlayerController::GetPawn()
{
	return reinterpret_cast<LREntity*>(ResolveHandle(m_hPawn()));
}

CCSPlayerPawn* CCSPlayerController::GetPlayerPawn()
{
	return reinterpret_cast<CCSPlayerPawn*>(ResolveHandle(m_hPlayerPawn()));
}
