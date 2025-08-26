#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoV2ServiceReference.h"

#include "BeamoV2ServiceReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoV2ServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoV2ServiceReference To JSON String")
	static FString BeamoV2ServiceReferenceToJsonString(const UBeamoV2ServiceReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoV2ServiceReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bEnabled, ServiceName, ImageId, TemplateId, Comments, ContainerHealthCheckPort, ImageCpuArch, Checksum, Dependencies, Components, Outer", NativeMakeFunc))
	static UBeamoV2ServiceReference* Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString ServiceName, FOptionalString ImageId, FOptionalString TemplateId, FOptionalString Comments, FOptionalInt32 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Checksum, FOptionalArrayOfBeamoV2ServiceDependencyReference Dependencies, FOptionalArrayOfBeamoV2ServiceComponent Components, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoV2ServiceReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoV2ServiceReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalString& TemplateId, FOptionalString& Comments, FOptionalInt32& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Checksum, FOptionalArrayOfBeamoV2ServiceDependencyReference& Dependencies, FOptionalArrayOfBeamoV2ServiceComponent& Components);
};