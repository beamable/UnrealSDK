#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBody.h"

#include "ContentBasicGetManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicGetManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="ContentBasicGetManifestRequestBody To JSON String")
	static FString ContentBasicGetManifestRequestBodyToJsonString(const UContentBasicGetManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make ContentBasicGetManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Uid, Outer", NativeMakeFunc))
	static UContentBasicGetManifestRequestBody* Make(FOptionalBeamContentManifestId Id, FOptionalString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break ContentBasicGetManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UContentBasicGetManifestRequestBody* Serializable, FOptionalBeamContentManifestId& Id, FOptionalString& Uid);
};