
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/MatchMakingRanking.h"
#include "AutoGen/MatchMakingWindowResp.h"

#include "MatchMakingMatchesPvpResponse.generated.h"

UCLASS(BlueprintType)
class UMatchMakingMatchesPvpResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Result")
	FString Result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Total Entries")
	int32 TotalEntries;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Rank")
	UMatchMakingRanking* PlayerRank;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Windows")
	TArray<UMatchMakingWindowResp*> Windows;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};