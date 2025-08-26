#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2PASuggestedIndex.h"

#include "BeamoV2PASuggestedIndexLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2PASuggestedIndexLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2PASuggestedIndex To JSON String")
	static FString BeamoV2PASuggestedIndexToJsonString(const UBeamoV2PASuggestedIndex* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2PASuggestedIndex", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoV2PASuggestedIndex* Make(FString Id, FString Namespace, double Weight, TArray<FString> Impact, TArray<FMapOfInt32> Index, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2PASuggestedIndex", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2PASuggestedIndex* Serializable, FString& Id, FString& Namespace, double& Weight, TArray<FString>& Impact, TArray<FMapOfInt32>& Index);
};