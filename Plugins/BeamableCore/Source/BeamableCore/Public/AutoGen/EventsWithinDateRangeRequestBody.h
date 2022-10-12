
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "EventsWithinDateRangeRequestBody.generated.h"

UCLASS(BlueprintType)
class UEventsWithinDateRangeRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From")
	FOptionalString From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To")
	FOptionalString To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query")
	FOptionalString Query;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit")
	FOptionalInt32 Limit;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};