
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt32.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "GetGroupsRequestBody.generated.h"

UCLASS(BlueprintType)
class UGetGroupsRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max")
	FOptionalInt32 Max;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Focus")
	FOptionalInt64 Focus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle")
	FOptionalInt32 Cycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="From")
	FOptionalInt32 From;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};