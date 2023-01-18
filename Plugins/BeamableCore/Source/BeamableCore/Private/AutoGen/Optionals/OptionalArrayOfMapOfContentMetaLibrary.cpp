

#include "AutoGen/Optionals/OptionalArrayOfMapOfContentMetaLibrary.h"

FOptionalArrayOfMapOfContentMeta UOptionalArrayOfMapOfContentMetaLibrary::MakeOptional(TArray<FMapOfContentMeta> Value)
{
	FOptionalArrayOfMapOfContentMeta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMapOfContentMeta UOptionalArrayOfMapOfContentMetaLibrary::Conv_OptionalFromValue(TArray<FMapOfContentMeta> Value)
{
	FOptionalArrayOfMapOfContentMeta Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalArrayOfMapOfContentMetaLibrary::HasValue(const FOptionalArrayOfMapOfContentMeta& Optional, TArray<FMapOfContentMeta>& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

TArray<FMapOfContentMeta> UOptionalArrayOfMapOfContentMetaLibrary::GetOptionalValue(const FOptionalArrayOfMapOfContentMeta& Optional, TArray<FMapOfContentMeta> DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

