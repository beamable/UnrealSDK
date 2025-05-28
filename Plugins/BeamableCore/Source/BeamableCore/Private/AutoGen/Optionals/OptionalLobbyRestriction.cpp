
#include "BeamableCore/Public/AutoGen/Optionals/OptionalLobbyRestriction.h"

FOptionalLobbyRestriction::FOptionalLobbyRestriction()
{
	Val = EBeamLobbyRestriction();
	IsSet = false;
}

FOptionalLobbyRestriction::FOptionalLobbyRestriction(EBeamLobbyRestriction Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalLobbyRestriction::GetAddr() const { return &Val; }

void FOptionalLobbyRestriction::Set(const void* Data)
{
	Val = *((EBeamLobbyRestriction*)Data);
	IsSet = true;
}