#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt64.h"

#include "GetStandingsRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UGetStandingsRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id", Category="Beam")
	FString TournamentId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max", Category="Beam")
	FOptionalInt32 Max = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus", Category="Beam")
	FOptionalInt64 Focus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle", Category="Beam")
	FOptionalInt32 Cycle = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From", Category="Beam")
	FOptionalInt32 From = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};