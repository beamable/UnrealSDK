#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoActorManifestChecksum.h"

#include "BeamoActorManifestChecksumLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoActorManifestChecksumLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoActorManifestChecksum To JSON String")
	static FString BeamoActorManifestChecksumToJsonString(const UBeamoActorManifestChecksum* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoActorManifestChecksum", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Checksum, CreatedAt, Outer", NativeMakeFunc))
	static UBeamoActorManifestChecksum* Make(FOptionalString Id, FOptionalString Checksum, FOptionalDateTime CreatedAt, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoActorManifestChecksum", meta=(NativeBreakFunc))
	static void Break(const UBeamoActorManifestChecksum* Serializable, FOptionalString& Id, FOptionalString& Checksum, FOptionalDateTime& CreatedAt);
};