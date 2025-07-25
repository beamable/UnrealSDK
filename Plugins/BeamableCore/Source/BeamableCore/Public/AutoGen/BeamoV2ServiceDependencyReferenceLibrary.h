#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceDependencyReference.h"

#include "BeamoV2ServiceDependencyReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceDependencyReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceDependencyReference To JSON String")
	static FString BeamoV2ServiceDependencyReferenceToJsonString(const UBeamoV2ServiceDependencyReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceDependencyReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="Id, StorageType, Outer", NativeMakeFunc))
	static UBeamoV2ServiceDependencyReference* Make(FOptionalString Id, FOptionalString StorageType, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceDependencyReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceDependencyReference* Serializable, FOptionalString& Id, FOptionalString& StorageType);
};