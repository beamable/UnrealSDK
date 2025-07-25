
#include "BeamableCore/Public/AutoGen/Optionals/OptionalAccountsBasicAccount.h"

FOptionalAccountsBasicAccount::FOptionalAccountsBasicAccount()
{
	Val = nullptr;
	IsSet = false;
}

FOptionalAccountsBasicAccount::FOptionalAccountsBasicAccount(UAccountsBasicAccount* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalAccountsBasicAccount::GetAddr() const { return &Val; }

void FOptionalAccountsBasicAccount::Set(const void* Data)
{
	Val = *((UAccountsBasicAccount**)Data);
	IsSet = true;
}