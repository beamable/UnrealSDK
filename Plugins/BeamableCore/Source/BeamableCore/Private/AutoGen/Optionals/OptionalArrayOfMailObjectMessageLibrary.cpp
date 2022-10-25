

#include "AutoGen/Optionals/OptionalArrayOfMailObjectMessageLibrary.h"

FOptionalArrayOfMailObjectMessage UOptionalArrayOfMailObjectMessageLibrary::MakeOptional(TArray<UMailObjectMessage*> Value)
{
	FOptionalArrayOfMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMailObjectMessage UOptionalArrayOfMailObjectMessageLibrary::Conv_OptionalFromValue(TArray<UMailObjectMessage*> Value)
{
	FOptionalArrayOfMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfMailObjectMessageLibrary::HasValue(const FOptionalArrayOfMailObjectMessage& Optional, TArray<UMailObjectMessage*>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<UMailObjectMessage*> UOptionalArrayOfMailObjectMessageLibrary::GetOptionalValue(const FOptionalArrayOfMailObjectMessage& Optional, TArray<UMailObjectMessage*> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

