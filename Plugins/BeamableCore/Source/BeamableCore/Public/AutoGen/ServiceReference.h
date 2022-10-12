
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

#include "ServiceReference.generated.h"

UCLASS(BlueprintType)
class UServiceReference : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Container Health Check Port")
	FOptionalInt64 ContainerHealthCheckPort;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Archived")
	bool bArchived;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name")
	FString ServiceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Enabled")
	bool bEnabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Arm")
	bool bArm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Checksum")
	FString Checksum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Template Id")
	FString TemplateId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Id")
	FString ImageId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Cpu Arch")
	FOptionalString ImageCpuArch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Dependencies")
	FOptionalArrayOfServiceDependencyReference Dependencies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Comments")
	FOptionalString Comments;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};