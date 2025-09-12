#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ContextRuleFilter.h"

#include "BeamoV2ContextRuleFilterLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ContextRuleFilterLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ContextRuleFilter To JSON String")
	static FString BeamoV2ContextRuleFilterToJsonString(const UBeamoV2ContextRuleFilter* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ContextRuleFilter", meta=(DefaultToSelf="Outer", AdvancedDisplay="PlayerIdOperationType, PathsOperationType, PlayerIds, Paths, X-custom, Outer", NativeMakeFunc))
	static UBeamoV2ContextRuleFilter* Make(FOptionalBeamoV2RuleOperationType PlayerIdOperationType, FOptionalBeamoV2RuleOperationType PathsOperationType, FOptionalArrayOfInt64 PlayerIds, FOptionalArrayOfString Paths, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ContextRuleFilter", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ContextRuleFilter* Serializable, FOptionalBeamoV2RuleOperationType& PlayerIdOperationType, FOptionalBeamoV2RuleOperationType& PathsOperationType, FOptionalArrayOfInt64& PlayerIds, FOptionalArrayOfString& Paths);
};