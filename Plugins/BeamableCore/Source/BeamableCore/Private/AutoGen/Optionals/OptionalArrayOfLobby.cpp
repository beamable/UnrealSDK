
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfLobby.h"

FOptionalArrayOfLobby::FOptionalArrayOfLobby()
{
	Val = TArray<ULobby*>();
	IsSet = false;
}

FOptionalArrayOfLobby::FOptionalArrayOfLobby(TArray<ULobby*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfLobby::GetAddr() const { return &Val; }

void FOptionalArrayOfLobby::Set(const void* Data)
{
	Val = *((TArray<ULobby*>*)Data);
	IsSet = true;
}