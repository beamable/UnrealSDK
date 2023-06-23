
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfLobbyPlayer.h"

FOptionalArrayOfLobbyPlayer::FOptionalArrayOfLobbyPlayer()
{
	Val = TArray<ULobbyPlayer*>();
	IsSet = false;
}

FOptionalArrayOfLobbyPlayer::FOptionalArrayOfLobbyPlayer(TArray<ULobbyPlayer*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfLobbyPlayer::GetAddr() const { return &Val; }

void FOptionalArrayOfLobbyPlayer::Set(const void* Data)
{
	Val = *((TArray<ULobbyPlayer*>*)Data);
	IsSet = true;
}