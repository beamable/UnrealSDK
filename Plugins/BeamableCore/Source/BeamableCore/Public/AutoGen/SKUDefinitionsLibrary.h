#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/SKUDefinitions.h"

#include "SKUDefinitionsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USKUDefinitionsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Json", DisplayName="SKUDefinitions To JSON String")
	static FString SKUDefinitionsToJsonString(const USKUDefinitions* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Make SKUDefinitions", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static USKUDefinitions* Make(int64 Version, int64 Created, TArray<USKU*> Definitions, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Commerce|Utils|Make/Break", DisplayName="Break SKUDefinitions", meta=(NativeBreakFunc))
	static void Break(const USKUDefinitions* Serializable, int64& Version, int64& Created, TArray<USKU*>& Definitions);
};