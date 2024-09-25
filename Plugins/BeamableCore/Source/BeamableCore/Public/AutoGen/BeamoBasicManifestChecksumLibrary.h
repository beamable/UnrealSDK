#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicManifestChecksum.h"

#include "BeamoBasicManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - BeamoBasicManifestChecksum To JSON String")
	static FString BeamoBasicManifestChecksumToJsonString(const UBeamoBasicManifestChecksum* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make BeamoBasicManifestChecksum", meta=(DefaultToSelf="Outer", AdvancedDisplay="Outer", NativeMakeFunc))
	static UBeamoBasicManifestChecksum* Make(FString Id, FString Checksum, int64 CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break BeamoBasicManifestChecksum", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicManifestChecksum* Serializable, FString& Id, FString& Checksum, int64& CreatedAt);
};