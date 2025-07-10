#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoActorManifest.h"

#include "BeamoActorManifestLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoActorManifestLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoActorManifest To JSON String")
	static FString BeamoActorManifestToJsonString(const UBeamoActorManifest* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoActorManifest", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, Created, CreatedByAccountId, Checksum, Comments, StorageGroupId, ServiceReferences, StorageReferences, Outer", NativeMakeFunc))
	static UBeamoActorManifest* Make(FOptionalString Id, FOptionalInt64 Created, FOptionalInt64 CreatedByAccountId, FOptionalString Checksum, FOptionalString Comments, FOptionalString StorageGroupId, FOptionalArrayOfBeamoActorServiceReference ServiceReferences, FOptionalArrayOfServiceStorageReference StorageReferences, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoActorManifest", meta=(NativeBreakFunc))
	static void Break(const UBeamoActorManifest* Serializable, FOptionalString& Id, FOptionalInt64& Created, FOptionalInt64& CreatedByAccountId, FOptionalString& Checksum, FOptionalString& Comments, FOptionalString& StorageGroupId, FOptionalArrayOfBeamoActorServiceReference& ServiceReferences, FOptionalArrayOfServiceStorageReference& StorageReferences);
};