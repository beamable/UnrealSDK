
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionLanguageContext.h"

FOptionalSessionLanguageContext::FOptionalSessionLanguageContext()
{
	Val = NewObject<USessionLanguageContext>(GetTransientPackage());
	IsSet = false;
}

FOptionalSessionLanguageContext::FOptionalSessionLanguageContext(USessionLanguageContext* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSessionLanguageContext::GetAddr() const { return &Val; }

void FOptionalSessionLanguageContext::Set(const void* Data)
{
	Val = *((USessionLanguageContext**)Data);
	IsSet = true;
}