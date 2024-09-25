#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"

#include "ClientManifestJsonResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientManifestJsonResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ClientManifestJsonResponse To JSON String")
	static FString ClientManifestJsonResponseToJsonString(const UClientManifestJsonResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ClientManifestJsonResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UClientManifestJsonResponse* Make(TArray<FBeamRemoteContentManifestEntry> Entries, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ClientManifestJsonResponse", meta=(NativeBreakFunc))
	static void Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries);
};