#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveBinaryRequestBody.h"

#include "SaveBinaryRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveBinaryRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SaveBinaryRequestBody To JSON String")
	static FString SaveBinaryRequestBodyToJsonString(const USaveBinaryRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SaveBinaryRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveBinaryRequestBody* Make(TArray<UBinaryDefinition*> Binary, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SaveBinaryRequestBody", meta=(NativeBreakFunc))
	static void Break(const USaveBinaryRequestBody* Serializable, TArray<UBinaryDefinition*>& Binary);
};