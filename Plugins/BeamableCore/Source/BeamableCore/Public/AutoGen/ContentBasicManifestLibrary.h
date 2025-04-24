#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifest.h"

#include "ContentBasicManifestLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ContentBasicManifest To JSON String")
	static FString ContentBasicManifestToJsonString(const UContentBasicManifest* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ContentBasicManifest", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, PublisherAccountId, Uid, Outer", NativeMakeFunc))
	static UContentBasicManifest* Make(FBeamContentManifestId Id, FString Checksum, int64 Created, TArray<UBaseContentReference*> References, FOptionalBool bArchived, FOptionalInt64 PublisherAccountId, FOptionalString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ContentBasicManifest", meta=(NativeBreakFunc))
	static void Break(const UContentBasicManifest* Serializable, FBeamContentManifestId& Id, FString& Checksum, int64& Created, TArray<UBaseContentReference*>& References, FOptionalBool& bArchived, FOptionalInt64& PublisherAccountId, FOptionalString& Uid);
};