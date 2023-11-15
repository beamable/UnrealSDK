
#include "BeamableCore/Public/AutoGen/Optionals/OptionalLobbyRestriction.h"

FOptionalLobbyRestriction::FOptionalLobbyRestriction()
{
	Val = ELobbyRestriction();
	IsSet = false;
}

FOptionalLobbyRestriction::FOptionalLobbyRestriction(ELobbyRestriction Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalLobbyRestriction::GetAddr() const { return &Val; }

void FOptionalLobbyRestriction::Set(const void* Data)
{
	Val = *((ELobbyRestriction*)Data);
	IsSet = true;
}