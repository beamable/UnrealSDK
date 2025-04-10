#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetCurrentManifestRequestBody.h"

#include "GetCurrentManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetCurrentManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|4 - Json", DisplayName="GetCurrentManifestRequestBody To JSON String")
	static FString GetCurrentManifestRequestBodyToJsonString(const UGetCurrentManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Make GetCurrentManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, Outer", NativeMakeFunc))
	static UGetCurrentManifestRequestBody* Make(FOptionalBool bArchived, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|3 - Backend", DisplayName="Break GetCurrentManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetCurrentManifestRequestBody* Serializable, FOptionalBool& bArchived);
};