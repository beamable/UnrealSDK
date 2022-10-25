

#include "AutoGen/Optionals/OptionalVariableReferenceLibrary.h"

FOptionalVariableReference UOptionalVariableReferenceLibrary::MakeOptional(UVariableReference* Value)
{
	FOptionalVariableReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalVariableReference UOptionalVariableReferenceLibrary::Conv_OptionalFromValue(UVariableReference* Value)
{
	FOptionalVariableReference Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalVariableReferenceLibrary::HasValue(const FOptionalVariableReference& Optional, UVariableReference*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UVariableReference* UOptionalVariableReferenceLibrary::GetOptionalValue(const FOptionalVariableReference& Optional, UVariableReference* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

