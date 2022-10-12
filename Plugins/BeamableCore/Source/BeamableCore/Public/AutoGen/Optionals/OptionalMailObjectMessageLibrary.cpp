

#include "OptionalMailObjectMessageLibrary.h"

FOptionalMailObjectMessage UOptionalMailObjectMessageLibrary::MakeOptionalMailObjectMessage(UMailObjectMessage* Value)
{
	FOptionalMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalMailObjectMessage UOptionalMailObjectMessageLibrary::Conv_OptionalMailObjectMessageFromValue(UMailObjectMessage* Value)
{
	FOptionalMailObjectMessage Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

