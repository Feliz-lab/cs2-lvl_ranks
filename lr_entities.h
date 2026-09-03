#pragma once

// Minimal schema views onto the game's closed-source entity classes - only the
// handful of fields levels_ranks actually reads. Mirrors what the old
// SchemaEntity headers gave us (CCSPlayerController::FromSlot / m_steamID /
// m_hPawn / m_hPlayerPawn / GetPlayerPawn, pawn team & health,
// CCSGameRules::m_bWarmupPeriod) with none of its SDK-version baggage.

#include <cstdint>
#include "schema.h"

// include/menus.h references these in OnTakeDamage* typedefs (previously
// completed by SchemaEntity's ctakedamageinfo.h). levels_ranks never uses the
// take-damage hooks, so forward declarations are enough.
class CTakeDamageInfo;
class CTakeDamageInfoContainer;

// GameEntitySystem() is declared by <entity2/entitysystem.h> (pulled in via
// schema.h) and defined in levels_ranks.cpp.

// Any entity: team + health live on CBaseEntity.
class LREntity
{
public:
	SCHEMA_FIELD(int32_t, CBaseEntity, m_iHealth)
	SCHEMA_FIELD(uint8_t, CBaseEntity, m_iTeamNum)
	int GetTeam() { return m_iTeamNum(); }
};

class CCSPlayerPawn : public LREntity
{
};

class CCSPlayerController
{
public:
	SCHEMA_FIELD(uint64_t, CBasePlayerController, m_steamID)
	SCHEMA_FIELD(uint32_t, CBasePlayerController, m_hPawn)       // raw CEntityHandle bits
	SCHEMA_FIELD(uint32_t, CCSPlayerController, m_hPlayerPawn)   // raw CEntityHandle bits
	SCHEMA_FIELD(uint8_t,  CBaseEntity,         m_iTeamNum)

	int GetTeam() { return m_iTeamNum(); }

	static CCSPlayerController* FromSlot(int iSlot);

	// Resolved live from the entity handles. Return nullptr when absent.
	LREntity*      GetPawn();
	CCSPlayerPawn* GetPlayerPawn();

	bool HasPawn()       { return GetPawn() != nullptr; }
	bool HasPlayerPawn() { return GetPlayerPawn() != nullptr; }
};

class CCSGameRules
{
public:
	SCHEMA_FIELD(bool, CCSGameRules, m_bWarmupPeriod)
};
