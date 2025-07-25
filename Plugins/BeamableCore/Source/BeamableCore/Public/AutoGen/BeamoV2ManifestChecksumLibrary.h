#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ManifestChecksum.h"

#include "BeamoV2ManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ManifestChecksum To JSON String")
	static FString BeamoV2ManifestChecksumToJsonString(const UBeamoV2ManifestChecksum* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ManifestChecksum", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Checksum, CreatedAt, Outer", NativeMakeFunc))
	static UBeamoV2ManifestChecksum* Make(FOptionalString Id, FOptionalString Checksum, FOptionalDateTime CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ManifestChecksum", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ManifestChecksum* Serializable, FOptionalString& Id, FOptionalString& Checksum, FOptionalDateTime& CreatedAt);
};