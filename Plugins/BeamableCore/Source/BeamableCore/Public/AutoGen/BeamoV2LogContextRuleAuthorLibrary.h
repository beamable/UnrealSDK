#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2LogContextRuleAuthor.h"

#include "BeamoV2LogContextRuleAuthorLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2LogContextRuleAuthorLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2LogContextRuleAuthor To JSON String")
	static FString BeamoV2LogContextRuleAuthorToJsonString(const UBeamoV2LogContextRuleAuthor* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2LogContextRuleAuthor", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2LogContextRuleAuthor* Make(FString Email, FString AccountId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2LogContextRuleAuthor", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2LogContextRuleAuthor* Serializable, FString& Email, FString& AccountId);
};