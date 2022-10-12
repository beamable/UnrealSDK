
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalArrayOfDatabaseMeasurement.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Link.h"

#include "DatabaseMeasurements.generated.h"

UCLASS(BlueprintType)
class UDatabaseMeasurements : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Measurements")
	FOptionalArrayOfDatabaseMeasurement Measurements;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Group Id")
	FOptionalString GroupId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Links")
	TArray<ULink*> Links;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Host Id")
	FOptionalString HostId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity")
	FOptionalString Granularity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End")
	FOptionalString End;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Database Name")
	FString DatabaseName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start")
	FOptionalString Start;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Process Id")
	FOptionalString ProcessId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};