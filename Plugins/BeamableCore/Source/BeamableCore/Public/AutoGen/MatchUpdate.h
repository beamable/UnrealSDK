
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalInt64.h"

#include "MatchUpdate.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UMatchUpdate : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Game", Category="Beam")
	FString Game;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Game Started", Category="Beam")
	bool bGameStarted;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Min Players Reached", Category="Beam")
	bool bMinPlayersReached;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	TArray<int64> Players;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining", Category="Beam")
	FOptionalInt64 SecondsRemaining;

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};