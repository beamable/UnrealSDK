#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ClientManifestResponse.h"

#include "ClientManifestResponseLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UClientManifestResponseLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ClientManifestResponse To JSON String")
	static FString ClientManifestResponseToJsonString(const UClientManifestResponse* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ClientManifestResponse", meta=(DefaultToSelf="Outer", AdvancedDisplay="CreatedAt, LatestUpdate, Outer", NativeMakeFunc))
	static UClientManifestResponse* Make(TArray<UClientContentInfo*> Items, FOptionalInt64 CreatedAt, FOptionalInt64 LatestUpdate, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ClientManifestResponse", meta=(NativeBreakFunc))
	static void Break(const UClientManifestResponse* Serializable, TArray<UClientContentInfo*>& Items, FOptionalInt64& CreatedAt, FOptionalInt64& LatestUpdate);
};