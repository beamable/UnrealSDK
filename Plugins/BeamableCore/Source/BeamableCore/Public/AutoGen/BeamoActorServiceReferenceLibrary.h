#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoActorServiceReference.h"

#include "BeamoActorServiceReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoActorServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoActorServiceReference To JSON String")
	static FString BeamoActorServiceReferenceToJsonString(const UBeamoActorServiceReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoActorServiceReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="bArchived, bEnabled, ServiceName, ImageId, TemplateId, Comments, ContainerHealthCheckPort, ImageCpuArch, Checksum, Dependencies, Components, Outer", NativeMakeFunc))
	static UBeamoActorServiceReference* Make(FOptionalBool bArchived, FOptionalBool bEnabled, FOptionalString ServiceName, FOptionalString ImageId, FOptionalString TemplateId, FOptionalString Comments, FOptionalInt32 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Checksum, FOptionalArrayOfServiceDependencyReference Dependencies, FOptionalArrayOfServiceComponent Components, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoActorServiceReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoActorServiceReference* Serializable, FOptionalBool& bArchived, FOptionalBool& bEnabled, FOptionalString& ServiceName, FOptionalString& ImageId, FOptionalString& TemplateId, FOptionalString& Comments, FOptionalInt32& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Checksum, FOptionalArrayOfServiceDependencyReference& Dependencies, FOptionalArrayOfServiceComponent& Components);
};