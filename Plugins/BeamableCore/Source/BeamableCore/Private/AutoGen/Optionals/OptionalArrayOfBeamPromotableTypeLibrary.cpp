

#include "AutoGen/Optionals/OptionalArrayOfBeamPromotableTypeLibrary.h"

FOptionalArrayOfBeamPromotableType UOptionalArrayOfBeamPromotableTypeLibrary::MakeOptional(TArray<EBeamPromotableType> Value)
{
	FOptionalArrayOfBeamPromotableType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfBeamPromotableType UOptionalArrayOfBeamPromotableTypeLibrary::Conv_OptionalFromValue(TArray<EBeamPromotableType> Value)
{
	FOptionalArrayOfBeamPromotableType Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfBeamPromotableTypeLibrary::HasValue(const FOptionalArrayOfBeamPromotableType& Optional, TArray<EBeamPromotableType>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<EBeamPromotableType> UOptionalArrayOfBeamPromotableTypeLibrary::GetOptionalValue(const FOptionalArrayOfBeamPromotableType& Optional, TArray<EBeamPromotableType> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

