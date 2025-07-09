

#include "AutoGen/Optionals/OptionalArrayOfServiceTemplateViewLibrary.h"

FOptionalArrayOfServiceTemplateView UOptionalArrayOfServiceTemplateViewLibrary::MakeOptional(TArray<UServiceTemplateView*> Value)
{
	FOptionalArrayOfServiceTemplateView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfServiceTemplateView UOptionalArrayOfServiceTemplateViewLibrary::Conv_OptionalFromValue(TArray<UServiceTemplateView*> Value)
{
	FOptionalArrayOfServiceTemplateView Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfServiceTemplateViewLibrary::HasValue(const FOptionalArrayOfServiceTemplateView& Optional, TArray<UServiceTemplateView*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UServiceTemplateView*> UOptionalArrayOfServiceTemplateViewLibrary::GetOptionalValue(const FOptionalArrayOfServiceTemplateView& Optional, TArray<UServiceTemplateView*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

