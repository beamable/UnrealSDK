

#include "OptionalVariableReferenceLibrary.h"

FOptionalVariableReference UOptionalVariableReferenceLibrary::MakeOptionalVariableReference(UVariableReference* Value)
{
	FOptionalVariableReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalVariableReference UOptionalVariableReferenceLibrary::Conv_OptionalVariableReferenceFromValue(UVariableReference* Value)
{
	FOptionalVariableReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

