#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/GetManifestDiffsRequestBody.h"

#include "GetManifestDiffsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetManifestDiffsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="GetManifestDiffsRequestBody To JSON String")
	static FString GetManifestDiffsRequestBodyToJsonString(const UGetManifestDiffsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make GetManifestDiffsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="FromUid, ToUid, Offset, Limit, Outer", NativeMakeFunc))
	static UGetManifestDiffsRequestBody* Make(FBeamContentManifestId ManifestId, FOptionalString FromUid, FOptionalString ToUid, FOptionalInt32 Offset, FOptionalInt32 Limit, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break GetManifestDiffsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UGetManifestDiffsRequestBody* Serializable, FBeamContentManifestId& ManifestId, FOptionalString& FromUid, FOptionalString& ToUid, FOptionalInt32& Offset, FOptionalInt32& Limit);
};