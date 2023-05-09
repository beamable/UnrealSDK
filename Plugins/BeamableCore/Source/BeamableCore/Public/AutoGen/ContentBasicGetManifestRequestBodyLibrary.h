#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentBasicGetManifestRequestBody.h"

#include "ContentBasicGetManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicGetManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ContentBasicGetManifestRequestBody To JSON String")
	static FString ContentBasicGetManifestRequestBodyToJsonString(const UContentBasicGetManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ContentBasicGetManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Outer", NativeMakeFunc))
	static UContentBasicGetManifestRequestBody* Make(FOptionalBeamContentManifestId Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ContentBasicGetManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UContentBasicGetManifestRequestBody* Serializable, FOptionalBeamContentManifestId& Id);
};