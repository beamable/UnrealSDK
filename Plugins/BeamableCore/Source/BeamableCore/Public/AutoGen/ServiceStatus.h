#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfServiceDependencyReference.h"

#include "ServiceStatus.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UServiceStatus : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Current", Category="Beam")
	bool bIsCurrent = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Running", Category="Beam")
	bool bRunning = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name", Category="Beam")
	FString ServiceName = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Image Id", Category="Beam")
	FString ImageId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Dependency References", Category="Beam")
	FOptionalArrayOfServiceDependencyReference ServiceDependencyReferences = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};