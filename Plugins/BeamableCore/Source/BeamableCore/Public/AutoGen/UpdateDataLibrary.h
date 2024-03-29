#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateData.h"

#include "UpdateDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UpdateData To JSON String")
	static FString UpdateDataToJsonString(const UUpdateData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UpdateData", meta=(DefaultToSelf="Outer", AdvancedDisplay="Deletes, Updates, Outer", NativeMakeFunc))
	static UUpdateData* Make(FOptionalArrayOfString Deletes, FOptionalMapOfString Updates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UpdateData", meta=(NativeBreakFunc))
	static void Break(const UUpdateData* Serializable, FOptionalArrayOfString& Deletes, FOptionalMapOfString& Updates);
};