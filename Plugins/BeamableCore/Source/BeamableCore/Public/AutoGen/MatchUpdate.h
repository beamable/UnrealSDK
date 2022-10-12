
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "MatchUpdate.generated.h"

UCLASS(BlueprintType)
class UMatchUpdate : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players")
	TArray<int64> Players;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining")
	FOptionalInt64 SecondsRemaining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Min Players Reached")
	bool bMinPlayersReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Game Started")
	bool bGameStarted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game")
	FString Game;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};