
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalRankEntry.h"
#include "AutoGen/RankEntry.h"

#include "LeaderBoardView.generated.h"

UCLASS(BlueprintType)
class ULeaderBoardView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lb Id")
	FString LbId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Board Size")
	int64 BoardSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rankgt")
	FOptionalRankEntry Rankgt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Rankings")
	TArray<URankEntry*> Rankings;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};