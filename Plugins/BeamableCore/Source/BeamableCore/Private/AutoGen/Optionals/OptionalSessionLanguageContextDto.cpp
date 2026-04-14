
#include "BeamableCore/Public/AutoGen/Optionals/OptionalSessionLanguageContextDto.h"

FOptionalSessionLanguageContextDto::FOptionalSessionLanguageContextDto()
{
	Val = NewObject<USessionLanguageContextDto>(GetTransientPackage());
	IsSet = false;
}

FOptionalSessionLanguageContextDto::FOptionalSessionLanguageContextDto(USessionLanguageContextDto* Val): Val(Val)
{
	IsSet = true;
}

const void* FOptionalSessionLanguageContextDto::GetAddr() const { return &Val; }

void FOptionalSessionLanguageContextDto::Set(const void* Data)
{
	Val = *((USessionLanguageContextDto**)Data);
	IsSet = true;
}