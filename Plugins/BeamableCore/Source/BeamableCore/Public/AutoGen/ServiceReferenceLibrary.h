#pragma once

#include "CoreMinimal.h"
#include "BeamableCore/Public/AutoGen/ServiceReference.h"

#include "ServiceReferenceLibrary.generated.h"


UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UServiceReferenceLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category="Beam|Json", DisplayName="Beam - ServiceReference To JSON String")
	static FString ServiceReferenceToJsonString(const UServiceReference* Serializable, const bool Pretty);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Make ServiceReference", meta=(DefaultToSelf="Outer", AdvancedDisplay="ContainerHealthCheckPort, ImageCpuArch, Comments, Components, Dependencies, Outer", NativeMakeFunc))
	static UServiceReference* Make(bool bArchived, bool bArm, bool bEnabled, FString ServiceName, FString Checksum, FString TemplateId, FString ImageId, FOptionalInt64 ContainerHealthCheckPort, FOptionalString ImageCpuArch, FOptionalString Comments, FOptionalArrayOfServiceComponent Components, FOptionalArrayOfServiceDependencyReference Dependencies, UObject* Outer);

	UFUNCTION(BlueprintPure, Category="Beam|Backend", DisplayName="Beam - Break ServiceReference", meta=(NativeBreakFunc))
	static void Break(const UServiceReference* Serializable, bool& bArchived, bool& bArm, bool& bEnabled, FString& ServiceName, FString& Checksum, FString& TemplateId, FString& ImageId, FOptionalInt64& ContainerHealthCheckPort, FOptionalString& ImageCpuArch, FOptionalString& Comments, FOptionalArrayOfServiceComponent& Components, FOptionalArrayOfServiceDependencyReference& Dependencies);
};