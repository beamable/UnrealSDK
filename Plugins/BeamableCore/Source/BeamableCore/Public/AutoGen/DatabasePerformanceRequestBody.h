
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "DatabasePerformanceRequestBody.generated.h"

UCLASS(BlueprintType)
class UDatabasePerformanceRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Date")
	FOptionalString EndDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Object Name")
	FString StorageObjectName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Granularity")
	FString Granularity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Date")
	FOptionalString StartDate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Period")
	FOptionalString Period;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};