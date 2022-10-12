
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

#include "ServiceStatus.generated.h"

UCLASS(BlueprintType)
class UServiceStatus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Current")
	bool bIsCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running")
	bool bRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name")
	FString ServiceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Id")
	FString ImageId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Dependency References")
	FOptionalArrayOfServiceDependencyReference ServiceDependencyReferences;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};