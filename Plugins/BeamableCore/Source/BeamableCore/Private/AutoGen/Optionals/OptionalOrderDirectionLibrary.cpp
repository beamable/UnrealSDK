

#include "AutoGen/Optionals/OptionalOrderDirectionLibrary.h"

FOptionalOrderDirection UOptionalOrderDirectionLibrary::MakeOptional(EBeamOrderDirection Value)
{
	FOptionalOrderDirection Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalOrderDirection UOptionalOrderDirectionLibrary::Conv_OptionalFromValue(EBeamOrderDirection Value)
{
	FOptionalOrderDirection Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalOrderDirectionLibrary::HasValue(const FOptionalOrderDirection& Optional, EBeamOrderDirection& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

EBeamOrderDirection UOptionalOrderDirectionLibrary::GetOptionalValue(const FOptionalOrderDirection& Optional, EBeamOrderDirection DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

