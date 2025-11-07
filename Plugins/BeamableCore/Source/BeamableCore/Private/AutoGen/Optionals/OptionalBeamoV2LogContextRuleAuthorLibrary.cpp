

#include "AutoGen/Optionals/OptionalBeamoV2LogContextRuleAuthorLibrary.h"

FOptionalBeamoV2LogContextRuleAuthor UOptionalBeamoV2LogContextRuleAuthorLibrary::MakeOptional(UBeamoV2LogContextRuleAuthor* Value)
{
	FOptionalBeamoV2LogContextRuleAuthor Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

FOptionalBeamoV2LogContextRuleAuthor UOptionalBeamoV2LogContextRuleAuthorLibrary::Conv_OptionalFromValue(UBeamoV2LogContextRuleAuthor* Value)
{
	FOptionalBeamoV2LogContextRuleAuthor Optional;
	Optional.Val = Value;
	Optional.IsSet = true;
	return Optional;
}

bool UOptionalBeamoV2LogContextRuleAuthorLibrary::HasValue(const FOptionalBeamoV2LogContextRuleAuthor& Optional, UBeamoV2LogContextRuleAuthor*& Value)
{
	Value = Optional.Val;
	return Optional.IsSet;
}

UBeamoV2LogContextRuleAuthor* UOptionalBeamoV2LogContextRuleAuthorLibrary::GetOptionalValue(const FOptionalBeamoV2LogContextRuleAuthor& Optional, UBeamoV2LogContextRuleAuthor* DefaultValue, bool& WasSet)
{
	WasSet = Optional.IsSet;
	return WasSet ? Optional.Val : DefaultValue;
}

