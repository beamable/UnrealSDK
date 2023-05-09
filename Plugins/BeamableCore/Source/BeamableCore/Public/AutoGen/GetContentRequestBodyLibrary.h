#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetContentRequestBody.h"

#include "GetContentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetContentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetContentRequestBody To JSON String")
	static FString GetContentRequestBodyToJsonString(const UGetContentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetContentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetContentRequestBody* Make(FBeamContentId ContentId, FString Version, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetContentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetContentRequestBody* Serializable, FBeamContentId& ContentId, FString& Version);
};