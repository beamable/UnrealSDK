#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceComponent.h"

#include "BeamoActorServiceReference.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UBeamoActorServiceReference : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived", Category="Beam")
	FOptionalBool bArchived = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Enabled", Category="Beam")
	FOptionalBool bEnabled = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FOptionalString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Id", Category="Beam")
	FOptionalString ImageId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Template Id", Category="Beam")
	FOptionalString TemplateId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments", Category="Beam")
	FOptionalString Comments = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Container Health Check Port", Category="Beam")
	FOptionalInt32 ContainerHealthCheckPort = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Cpu Arch", Category="Beam")
	FOptionalString ImageCpuArch = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum", Category="Beam")
	FOptionalString Checksum = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dependencies", Category="Beam")
	FOptionalArrayOfServiceDependencyReference Dependencies = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Components", Category="Beam")
	FOptionalArrayOfServiceComponent Components = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};