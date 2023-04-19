
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfGroupScoreBinding.h"

FOptionalArrayOfGroupScoreBinding::FOptionalArrayOfGroupScoreBinding()
{
	Val = TArray<UGroupScoreBinding*>();
	IsSet = false;
}

FOptionalArrayOfGroupScoreBinding::FOptionalArrayOfGroupScoreBinding(TArray<UGroupScoreBinding*> Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalArrayOfGroupScoreBinding::GetAddr() const { return &Val; }

void FOptionalArrayOfGroupScoreBinding::Set(const void* Data)
{
	Val = *((TArray<UGroupScoreBinding*>*)Data);
	IsSet = true;
}