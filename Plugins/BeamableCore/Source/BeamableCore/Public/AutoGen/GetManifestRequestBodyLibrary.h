
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/GetManifestRequestBody.h"

#include "GetManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - GetManifestRequestBody To JSON String")
	static FString GetManifestRequestBodyToJsonString(const UGetManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make GetManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, Outer", NativeMakeFunc))
	static UGetManifestRequestBody* Make(FString Id, FOptionalBool bArchived, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break GetManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetManifestRequestBody* Serializable, FString& Id, FOptionalBool& bArchived);
};