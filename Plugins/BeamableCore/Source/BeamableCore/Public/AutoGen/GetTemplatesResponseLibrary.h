#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetTemplatesResponse.h"

#include "GetTemplatesResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetTemplatesResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetTemplatesResponse To JSON String")
	static FString GetTemplatesResponseToJsonString(const UGetTemplatesResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetTemplatesResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetTemplatesResponse* Make(TArray<UServiceTemplate*> Templates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetTemplatesResponse", meta=(NativeBreakFunc))
	static void Break(const UGetTemplatesResponse* Serializable, TArray<UServiceTemplate*>& Templates);
};