#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetContentRequestBody.h"

#include "GetContentRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetContentRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetContentRequestBody To JSON String")
	static FString GetContentRequestBodyToJsonString(const UGetContentRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetContentRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UGetContentRequestBody* Make(FBeamContentId ContentId, FString Version, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetContentRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetContentRequestBody* Serializable, FBeamContentId& ContentId, FString& Version);
};