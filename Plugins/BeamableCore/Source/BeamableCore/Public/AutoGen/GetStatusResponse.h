
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/ServiceStatus.h"
#include "AutoGen/Optionals/OptionalArrayOfServiceStorageStatus.h"

#include "GetStatusResponse.generated.h"

UCLASS(BlueprintType)
class UGetStatusResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Services")
	TArray<UServiceStatus*> Services;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Current")
	bool bIsCurrent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Statuses")
	FOptionalArrayOfServiceStorageStatus StorageStatuses;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};