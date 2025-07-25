#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2SupportedFederation.h"

#include "BeamoV2SupportedFederationLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2SupportedFederationLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2SupportedFederation To JSON String")
	static FString BeamoV2SupportedFederationToJsonString(const UBeamoV2SupportedFederation* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2SupportedFederation", meta=(DefaultToSelf="Outer", AdvancedDisplay="Type, NameSpace, Outer", NativeMakeFunc))
	static UBeamoV2SupportedFederation* Make(FOptionalBeamoV2FederationType Type, FOptionalString NameSpace, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2SupportedFederation", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2SupportedFederation* Serializable, FOptionalBeamoV2FederationType& Type, FOptionalString& NameSpace);
};