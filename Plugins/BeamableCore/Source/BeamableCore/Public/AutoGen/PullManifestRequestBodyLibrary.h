#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PullManifestRequestBody.h"

#include "PullManifestRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPullManifestRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="PullManifestRequestBody To JSON String")
	static FString PullManifestRequestBodyToJsonString(const UPullManifestRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make PullManifestRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Outer", NativeMakeFunc))
	static UPullManifestRequestBody* Make(FBeamPid SourceRealmPid, FOptionalBeamContentManifestId Id, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break PullManifestRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPullManifestRequestBody* Serializable, FBeamPid& SourceRealmPid, FOptionalBeamContentManifestId& Id);
};