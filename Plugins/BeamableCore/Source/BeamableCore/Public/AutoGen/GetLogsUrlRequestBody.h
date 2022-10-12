
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "GetLogsUrlRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetLogsUrlRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time")
	FOptionalInt64 StartTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Service Name")
	FString ServiceName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Next Token")
	FOptionalString NextToken;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Filter")
	FOptionalString Filter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time")
	FOptionalInt64 EndTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};