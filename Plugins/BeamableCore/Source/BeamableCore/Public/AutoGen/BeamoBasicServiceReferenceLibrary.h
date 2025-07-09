#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/BeamoBasicServiceReference.h"

#include "BeamoBasicServiceReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UBeamoBasicServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Json", DisplayName="BeamoBasicServiceReference To JSON String")
	static FString BeamoBasicServiceReferenceToJsonString(const UBeamoBasicServiceReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Make BeamoBasicServiceReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="ContainerHealthCheckPort, ImageCpuArch, Comments, Components, Dependencies, Outer", NativeMakeFunc))
	static UBeamoBasicServiceReference* Make(bool bArchived, bool bArm, bool bEnabled, FString ServiceName, FString Checksum, FString TemplateId, FString ImageId, FOptionalInt64 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Comments, FOptionalArrayOfServiceComponent Components, FOptionalArrayOfServiceDependencyReference Dependencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Beamo|Utils|Make/Break", DisplayName="Break BeamoBasicServiceReference", meta=(NativeBreakFunc))
	static void Break(const UBeamoBasicServiceReference* Serializable, bool& bArchived, bool& bArm, bool& bEnabled, FString& ServiceName, FString& Checksum, FString& TemplateId, FString& ImageId, FOptionalInt64& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Comments, FOptionalArrayOfServiceComponent& Components, FOptionalArrayOfServiceDependencyReference& Dependencies);
};