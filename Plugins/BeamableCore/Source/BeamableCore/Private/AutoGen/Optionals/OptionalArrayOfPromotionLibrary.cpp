

#include "AutoGen/Optionals/OptionalArrayOfPromotionLibrary.h"

FOptionalArrayOfPromotion UOptionalArrayOfPromotionLibrary::MakeOptional(TArray<UPromotion*> Value)
{
	FOptionalArrayOfPromotion Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfPromotion UOptionalArrayOfPromotionLibrary::Conv_OptionalFromValue(TArray<UPromotion*> Value)
{
	FOptionalArrayOfPromotion Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfPromotionLibrary::HasValue(const FOptionalArrayOfPromotion& Optional, TArray<UPromotion*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UPromotion*> UOptionalArrayOfPromotionLibrary::GetOptionalValue(const FOptionalArrayOfPromotion& Optional, TArray<UPromotion*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

