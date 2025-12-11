
#include "BeamableCore/Public/AutoGen/Optionals/OptionalTransactionState.h"

FOptionalTransactionState::FOptionalTransactionState()
{
	Val = EBeamTransactionState();
	IsSet = false;
}

FOptionalTransactionState::FOptionalTransactionState(EBeamTransactionState Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalTransactionState::GetAddr() const { return &Val; }

void FOptionalTransactionState::Set(const void* Data)
{
	Val = *((EBeamTransactionState*)Data);
	IsSet = true;
}