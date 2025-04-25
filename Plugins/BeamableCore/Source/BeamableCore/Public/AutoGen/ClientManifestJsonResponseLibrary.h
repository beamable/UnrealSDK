#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientManifestJsonResponse.h"

#include "ClientManifestJsonResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientManifestJsonResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ClientManifestJsonResponse To JSON String")
	static FString ClientManifestJsonResponseToJsonString(const UClientManifestJsonResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ClientManifestJsonResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="Uid, PublisherAccountId, Outer", NativeMakeFunc))
	static UClientManifestJsonResponse* Make(TArray<FBeamRemoteContentManifestEntry> Entries, FOptionalString Uid, FOptionalInt64 PublisherAccountId, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ClientManifestJsonResponse", meta=(NativeBreakFunc))
	static void Break(const UClientManifestJsonResponse* Serializable, TArray<FBeamRemoteContentManifestEntry>& Entries, FOptionalString& Uid, FOptionalInt64& PublisherAccountId);
};