#pragma once

// Minimal self-contained schema-field access layer.
//
// Replaces the bundled pisex/SchemaEntity, whose public version no longer
// compiles against a current alliedmodders/hl2sdk-cs2 (it still references
// Ray_t / HitGroup_t / FL_PAWN_FAKECLIENT / NetworkStateChanged_t etc.).
// Field offsets are resolved by name against the live game schema, so this
// keeps working across CS2 updates without hardcoding any offsets.
//
// Uses the SDK-provided g_pSchemaSystem (populated by the GET_V_IFACE_ANY in
// LR::Load) rather than declaring our own, to avoid a multiple-definition
// clash with the copy in hl2sdk's prebuilt interfaces.a.

#include <cstdint>
#include <type_traits>
#include <entity2/entitysystem.h>
#include <schemasystem/schemasystem.h>

namespace lrschema
{
	// Byte offset of className::memberName, via the SDK's own
	// ISchemaSystemTypeScope::FindDeclaredClass(). Returns 0 on failure so a
	// miss reads *(this + 0) instead of corrupting memory.
	int32_t GetOffset(const char* className, const char* memberName);
}

#define SCHEMA_FIELD(type, className, propName)                                                         \
	std::add_lvalue_reference_t<type> propName()                                                        \
	{                                                                                                  \
		static const int32_t offset = lrschema::GetOffset(#className, #propName);                        \
		return *reinterpret_cast<std::add_pointer_t<type>>(reinterpret_cast<intptr_t>(this) + offset);   \
	}
