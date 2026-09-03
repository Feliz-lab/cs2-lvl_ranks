#include "schema.h"
#include <tier1/strtools.h>

// g_pSchemaSystem: declared by <schemasystem/schemasystem.h>, storage from
// interfaces.a, populated by LR::Load()'s GET_V_IFACE_ANY.

int32_t lrschema::GetOffset(const char* className, const char* memberName)
{
	if (!g_pSchemaSystem)
		return 0;

	CSchemaSystemTypeScope* pType = g_pSchemaSystem->FindTypeScopeForModule("libserver.so");
	if (!pType)
		return 0;

	CSchemaClassInfo* pClassInfo = pType->FindDeclaredClass(className).Get();
	if (!pClassInfo)
		return 0;

	SchemaClassFieldData_t* pFields = pClassInfo->m_pFields;
	for (uint16 i = 0; i < pClassInfo->m_nFieldCount; i++)
	{
		if (!V_stricmp(pFields[i].m_pszName, memberName))
			return pFields[i].m_nSingleInheritanceOffset;
	}

	return 0;
}
