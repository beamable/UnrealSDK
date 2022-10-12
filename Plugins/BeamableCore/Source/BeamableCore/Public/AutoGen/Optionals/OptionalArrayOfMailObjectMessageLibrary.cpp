

#include "OptionalArrayOfMailObjectMessageLibrary.h"

FOptionalArrayOfMailObjectMessage UOptionalArrayOfMailObjectMessageLibrary::MakeOptionalArrayOfMailObjectMessage(TArray<UMailObjectMessage*> Value)
{
	FOptionalArrayOfMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalArrayOfMailObjectMessage UOptionalArrayOfMailObjectMessageLibrary::Conv_OptionalArrayOfMailObjectMessageFromValue(TArray<UMailObjectMessage*> Value)
{
	FOptionalArrayOfMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

