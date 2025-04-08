#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PullAllManifestsRequestBody.h"

#include "PullAllManifestsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPullAllManifestsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Json", DisplayName="PullAllManifestsRequestBody To JSON String")
	static FString PullAllManifestsRequestBodyToJsonString(const UPullAllManifestsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Make PullAllManifestsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPullAllManifestsRequestBody* Make(FBeamPid SourceRealmPid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Shared|Backend", DisplayName="Break PullAllManifestsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPullAllManifestsRequestBody* Serializable, FBeamPid& SourceRealmPid);
};