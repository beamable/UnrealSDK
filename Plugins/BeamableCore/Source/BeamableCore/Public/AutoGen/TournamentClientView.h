
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "TournamentClientView.generated.h"

UCLASS(BlueprintType)
class UTournamentClientView : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tournament Id")
	FString TournamentId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Start Time Utc")
	FString StartTimeUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Seconds Remaining")
	int64 SecondsRemaining;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Cycle")
	int32 Cycle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="End Time Utc")
	FString EndTimeUtc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content Id")
	FString ContentId;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};