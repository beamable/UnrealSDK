
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ServiceStorageStatus.generated.h"

UCLASS(BlueprintType)
class UServiceStorageStatus : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id")
	FString Id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Type")
	FString StorageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Running")
	bool bIsRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Is Current")
	bool bIsCurrent;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};