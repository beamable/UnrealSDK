#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/UploadURL.h"

#include "UploadURLLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UUploadURLLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - UploadURL To JSON String")
	static FString UploadURLToJsonString(const UUploadURL* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make UploadURL", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UUploadURL* Make(FString Key, FString Url, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break UploadURL", meta=(NativeBreakFunc))
	static void Break(const UUploadURL* Serializable, FString& Key, FString& Url);
};