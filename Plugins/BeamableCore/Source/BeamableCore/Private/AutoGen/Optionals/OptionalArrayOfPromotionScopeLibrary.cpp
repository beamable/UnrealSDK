

#include "AutoGen/Optionals/OptionalArrayOfPromotionScopeLibrary.h"

FOptionalArrayOfPromotionScope UOptionalArrayOfPromotionScopeLibrary::MakeOptional(TArray<UPromotionScope*> Value)
{
	FOptionalArrayOfPromotionScope Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPromotionScope UOptionalArrayOfPromotionScopeLibrary::Conv_OptionalFromValue(TArray<UPromotionScope*> Value)
{
	FOptionalArrayOfPromotionScope Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPromotionScopeLibrary::HasValue(const FOptionalArrayOfPromotionScope& Optional, TArray<UPromotionScope*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPromotionScope*> UOptionalArrayOfPromotionScopeLibrary::GetOptionalValue(const FOptionalArrayOfPromotionScope& Optional, TArray<UPromotionScope*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

