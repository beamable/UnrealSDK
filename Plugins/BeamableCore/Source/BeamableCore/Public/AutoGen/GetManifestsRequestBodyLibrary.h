#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestsRequestBody.h"

#include "GetManifestsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|4 - Json", DisplayName="GetManifestsRequestBody To JSON String")
	static FString GetManifestsRequestBodyToJsonString(const UGetManifestsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Make GetManifestsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, Limit, Offset, Outer", NativeMakeFunc))
	static UGetManifestsRequestBody* Make(FOptionalBool bArchived, FOptionalInt32 Limit, FOptionalInt32 Offset, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Break GetManifestsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetManifestsRequestBody* Serializable, FOptionalBool& bArchived, FOptionalInt32& Limit, FOptionalInt32& Offset);
};