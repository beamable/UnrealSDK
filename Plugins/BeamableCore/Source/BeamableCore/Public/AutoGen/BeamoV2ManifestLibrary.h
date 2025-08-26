#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2Manifest.h"

#include "BeamoV2ManifestLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2Manifest To JSON String")
	static FString BeamoV2ManifestToJsonString(const UBeamoV2Manifest* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2Manifest", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Created, CreatedByAccountId, Checksum, Comments, StorageGroupId, ServiceReferences, StorageReferences, Outer", NativeMakeFunc))
	static UBeamoV2Manifest* Make(FOptionalString Id, FOptionalInt64 Created, FOptionalInt64 CreatedByAccountId, FOptionalString Checksum, FOptionalString Comments, FOptionalString StorageGroupId, FOptionalArrayOfBeamoV2ServiceReference ServiceReferences, FOptionalArrayOfBeamoV2ServiceStorageReference StorageReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2Manifest", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2Manifest* Serializable, FOptionalString& Id, FOptionalInt64& Created, FOptionalInt64& CreatedByAccountId, FOptionalString& Checksum, FOptionalString& Comments, FOptionalString& StorageGroupId, FOptionalArrayOfBeamoV2ServiceReference& ServiceReferences, FOptionalArrayOfBeamoV2ServiceStorageReference& StorageReferences);
};