#pragma once

#include "CoreMinimal.h"
#include "BeamableUnreal\AutoGen/MSPlaygroundAddRequestArgs.h"

#include "MSPlaygroundAddRequestArgsLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UMSPlaygroundAddRequestArgsLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - MSPlaygroundAddRequestArgs To JSON String")
	static FString MSPlaygroundAddRequestArgsToJsonString(const UMSPlaygroundAddRequestArgs* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make MSPlaygroundAddRequestArgs", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UMSPlaygroundAddRequestArgs* Make(int32 A, int32 B, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break MSPlaygroundAddRequestArgs", meta=(NativeBreakFunc))
	static void Break(const UMSPlaygroundAddRequestArgs* Serializable, int32& A, int32& B);
};