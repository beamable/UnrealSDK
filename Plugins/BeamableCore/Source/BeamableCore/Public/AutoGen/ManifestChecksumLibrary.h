
#pragma once

#include "CoreMinimal.h"
#include "AutoGen/ManifestChecksum.h"

#include "ManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ManifestChecksum To JSON String")
	static FString ManifestChecksumToJsonString(const UManifestChecksum* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ManifestChecksum", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UManifestChecksum* Make(FString Id, FString Checksum, int64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ManifestChecksum", meta=(NativeBreakFunc))
	static void Break(const UManifestChecksum* Serializable, FString& Id, FString& Checksum, int64& CreatedAt);
};