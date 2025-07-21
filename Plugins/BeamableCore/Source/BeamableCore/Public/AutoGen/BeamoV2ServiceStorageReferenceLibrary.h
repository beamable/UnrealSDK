#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceStorageReference.h"

#include "BeamoV2ServiceStorageReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceStorageReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceStorageReference To JSON String")
	static FString BeamoV2ServiceStorageReferenceToJsonString(const UBeamoV2ServiceStorageReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceStorageReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bEnabled, Id, StorageType, TemplateId, Checksum, Outer", NativeMakeFunc))
	static UBeamoV2ServiceStorageReference* Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString Id, FOptionalString StorageType, FOptionalString TemplateId, FOptionalString Checksum, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceStorageReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceStorageReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& Id, FOptionalString& StorageType, FOptionalString& TemplateId, FOptionalString& Checksum);
};