#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PullAllManifestsRequestBody.h"

#include "PullAllManifestsRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPullAllManifestsRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="PullAllManifestsRequestBody To JSON String")
	static FString PullAllManifestsRequestBodyToJsonString(const UPullAllManifestsRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make PullAllManifestsRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UPullAllManifestsRequestBody* Make(FBeamPid SourceRealmPid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break PullAllManifestsRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPullAllManifestsRequestBody* Serializable, FBeamPid& SourceRealmPid);
};