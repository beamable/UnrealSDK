#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveBinaryResponse.h"

#include "SaveBinaryResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveBinaryResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="SaveBinaryResponse To JSON String")
	static FString SaveBinaryResponseToJsonString(const USaveBinaryResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make SaveBinaryResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveBinaryResponse* Make(TArray<UBinaryReference*> Binary, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break SaveBinaryResponse", meta=(NativeBreakFunc))
	static void Break(const USaveBinaryResponse* Serializable, TArray<UBinaryReference*>& Binary);
};