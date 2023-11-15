#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal\AutoGen/MSPlaygroundMsAddResponse.h"

#include "MSPlaygroundMsAddResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UMSPlaygroundMsAddResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MSPlaygroundMsAddResponse To JSON String")
	static FString MSPlaygroundMsAddResponseToJsonString(const UMSPlaygroundMsAddResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MSPlaygroundMsAddResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMSPlaygroundMsAddResponse* Make(int32 Value, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MSPlaygroundMsAddResponse", meta=(NativeBreakFunc))
	static void Break(const UMSPlaygroundMsAddResponse* Serializable, int32& Value);
};