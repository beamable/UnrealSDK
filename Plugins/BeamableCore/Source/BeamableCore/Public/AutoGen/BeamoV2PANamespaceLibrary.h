#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PANamespace.h"

#include "BeamoV2PANamespaceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2PANamespaceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2PANamespace To JSON String")
	static FString BeamoV2PANamespaceToJsonString(const UBeamoV2PANamespace* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2PANamespace", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2PANamespace* Make(FString Namespace, FString Type, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2PANamespace", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2PANamespace* Serializable, FString& Namespace, FString& Type);
};