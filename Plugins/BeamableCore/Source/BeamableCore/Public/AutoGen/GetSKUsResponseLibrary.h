#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetSKUsResponse.h"

#include "GetSKUsResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetSKUsResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="GetSKUsResponse To JSON String")
	static FString GetSKUsResponseToJsonString(const UGetSKUsResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make GetSKUsResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetSKUsResponse* Make(USKUDefinitions* Skus, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break GetSKUsResponse", meta=(NativeBreakFunc))
	static void Break(const UGetSKUsResponse* Serializable, USKUDefinitions*& Skus);
};