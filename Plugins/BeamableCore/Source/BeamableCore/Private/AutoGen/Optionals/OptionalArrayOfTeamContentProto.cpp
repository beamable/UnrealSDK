
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTeamContentProto.h"

FOptionalArrayOfTeamContentProto::FOptionalArrayOfTeamContentProto()
{
	Val = TArray<UTeamContentProto*>();
	IsSet = false;
}

FOptionalArrayOfTeamContentProto::FOptionalArrayOfTeamContentProto(TArray<UTeamContentProto*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfTeamContentProto::GetAddr() const { return &Val; }

void FOptionalArrayOfTeamContentProto::Set(const void* Data)
{
	Val = *((TArray<UTeamContentProto*>*)Data);
	IsSet = true;
}