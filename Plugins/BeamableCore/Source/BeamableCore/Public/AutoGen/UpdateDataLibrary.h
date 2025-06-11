#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UpdateData.h"

#include "UpdateDataLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUpdateDataLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Json", DisplayName="UpdateData To JSON String")
	static FString UpdateDataToJsonString(const UUpdateData* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Make UpdateData", meta=(DefaultToSelf="Outer", AdvancedDisplay="Deletes, Updates, Outer", NativeMakeFunc))
	static UUpdateData* Make(FOptionalArrayOfString Deletes, FOptionalMapOfString Updates, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Lobby|Utils|Make/Break", DisplayName="Break UpdateData", meta=(NativeBreakFunc))
	static void Break(const UUpdateData* Serializable, FOptionalArrayOfString& Deletes, FOptionalMapOfString& Updates);
};