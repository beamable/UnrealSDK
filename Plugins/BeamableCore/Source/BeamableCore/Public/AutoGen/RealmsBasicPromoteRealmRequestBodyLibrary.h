#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/RealmsBasicPromoteRealmRequestBody.h"

#include "RealmsBasicPromoteRealmRequestBodyLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API URealmsBasicPromoteRealmRequestBodyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Json", DisplayName="RealmsBasicPromoteRealmRequestBody To JSON String")
	static FString RealmsBasicPromoteRealmRequestBodyToJsonString(const URealmsBasicPromoteRealmRequestBody* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Make RealmsBasicPromoteRealmRequestBody", meta=(DefaultToSelf="Outer", AdvancedDisplay="Promotions, ContentManifestIds, Outer", NativeMakeFunc))
	static URealmsBasicPromoteRealmRequestBody* Make(FBeamPid SourcePid, FOptionalArrayOfString Promotions, FOptionalArrayOfString ContentManifestIds, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Realms|Utils|Make/Break", DisplayName="Break RealmsBasicPromoteRealmRequestBody", meta=(NativeBreakFunc))
	static void Break(const URealmsBasicPromoteRealmRequestBody* Serializable, FBeamPid& SourcePid, FOptionalArrayOfString& Promotions, FOptionalArrayOfString& ContentManifestIds);
};