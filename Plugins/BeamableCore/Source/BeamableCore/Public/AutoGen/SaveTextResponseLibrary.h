#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveTextResponse.h"

#include "SaveTextResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveTextResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SaveTextResponse To JSON String")
	static FString SaveTextResponseToJsonString(const USaveTextResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SaveTextResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveTextResponse* Make(TArray<UTextReference*> Text, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SaveTextResponse", meta=(NativeBreakFunc))
	static void Break(const USaveTextResponse* Serializable, TArray<UTextReference*>& Text);
};