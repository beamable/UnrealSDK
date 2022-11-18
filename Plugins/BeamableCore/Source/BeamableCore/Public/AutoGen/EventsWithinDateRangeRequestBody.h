
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalString.h"
#include "AutoGen/Optionals/OptionalInt32.h"

#include "EventsWithinDateRangeRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UEventsWithinDateRangeRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalString From;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="To", Category="Beam")
	FOptionalString To;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Query", Category="Beam")
	FOptionalString Query;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Limit", Category="Beam")
	FOptionalInt32 Limit;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};