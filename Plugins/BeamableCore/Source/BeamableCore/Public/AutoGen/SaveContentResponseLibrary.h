#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SaveContentResponse.h"

#include "SaveContentResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USaveContentResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - SaveContentResponse To JSON String")
	static FString SaveContentResponseToJsonString(const USaveContentResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make SaveContentResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USaveContentResponse* Make(TArray<UContentReference*> Content, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break SaveContentResponse", meta=(NativeBreakFunc))
	static void Break(const USaveContentResponse* Serializable, TArray<UContentReference*>& Content);
};