#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ContentBasicManifestChecksum.h"

#include "ContentBasicManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UContentBasicManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Json", DisplayName="ContentBasicManifestChecksum To JSON String")
	static FString ContentBasicManifestChecksumToJsonString(const UContentBasicManifestChecksum* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Make ContentBasicManifestChecksum", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, Uid, Outer", NativeMakeFunc))
	static UContentBasicManifestChecksum* Make(FBeamContentManifestId Id, FString Checksum, int64 CreatedAt, FOptionalBool bArchived, FOptionalString Uid, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Content|Utils|Make/Break", DisplayName="Break ContentBasicManifestChecksum", meta=(NativeBreakFunc))
	static void Break(const UContentBasicManifestChecksum* Serializable, FBeamContentManifestId& Id, FString& Checksum, int64& CreatedAt, FOptionalBool& bArchived, FOptionalString& Uid);
};