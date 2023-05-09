#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/PromoteRealmRequestBody.h"

#include "PromoteRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPromoteRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - PromoteRealmRequestBody To JSON String")
	static FString PromoteRealmRequestBodyToJsonString(const UPromoteRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make PromoteRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Promotions, ContentManifestIds, Outer", NativeMakeFunc))
	static UPromoteRealmRequestBody* Make(FBeamPid SourcePid, FOptionalArrayOfString Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break PromoteRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const UPromoteRealmRequestBody* Serializable, FBeamPid& SourcePid, FOptionalArrayOfString& Promotions, FOptionalArrayOfString& ContentManifestIds);
};