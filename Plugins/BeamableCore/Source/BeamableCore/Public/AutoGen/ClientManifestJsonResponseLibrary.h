#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"

#include "ClientManifestJsonResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientManifestJsonResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|4 - Json", DisplayName="ClientManifestJsonResponse To JSON String")
	static FString ClientManifestJsonResponseToJsonString(const UClientManifestJsonResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Make ClientManifestJsonResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Uid, Outer", NativeMakeFunc))
	static UClientManifestJsonResponse* Make(TArray<FBeamRemoteContentManifestEntry> Entries, FOptionalString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|3 - Backend", DisplayName="Break ClientManifestJsonResponse", meta=(NativeBreakFunc))
	static void Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries, FOptionalString& Uid);
};