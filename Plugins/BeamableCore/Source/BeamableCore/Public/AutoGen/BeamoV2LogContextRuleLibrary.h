#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRule.h"

#include "BeamoV2LogContextRuleLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2LogContextRuleLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2LogContextRule To JSON String")
	static FString BeamoV2LogContextRuleToJsonString(const UBeamoV2LogContextRule* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2LogContextRule", meta=(DefaultToSelf="Outer", AdvancedDisplay="Name, Description, CreatedAt, UpdatedAt, ExpiresAt, Outer", NativeMakeFunc))
	static UBeamoV2LogContextRule* Make(bool bEnabled, FString Id, UBeamoV2LogContextRuleAuthor* Author, TArray<UBeamoV2ContextRuleFilter*> RuleFilters, FOptionalString Name, FOptionalString Description, FOptionalInt64 CreatedAt, FOptionalInt64 UpdatedAt, FOptionalInt64 ExpiresAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2LogContextRule", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2LogContextRule* Serializable, bool& bEnabled, FString& Id, UBeamoV2LogContextRuleAuthor*& Author, TArray<UBeamoV2ContextRuleFilter*>& RuleFilters, FOptionalString& Name, FOptionalString& Description, FOptionalInt64& CreatedAt, FOptionalInt64& UpdatedAt, FOptionalInt64& ExpiresAt);
};