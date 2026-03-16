
#include "BeamableCore/Public/AutoGen/Optionals/OptionalCatalog.h"

FOptionalCatalog::FOptionalCatalog()
{
	Val = NewObject<UCatalog>(GetTransientPackage());
	IsSet = false;
}

FOptionalCatalog::FOptionalCatalog(UCatalog* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalCatalog::GetAddr() const { return &Val; }

void FOptionalCatalog::Set(const void* Data)
{
	Val = *((UCatalog**)Data);
	IsSet = true;
}