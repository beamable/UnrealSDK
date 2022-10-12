
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Optionals/OptionalBool.h"

#include "LeaderboardPlayerAssignmentRequestBody.generated.h"

UCLASS(BlueprintType)
class ULeaderboardPlayerAssignmentRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Board Id")
	FString BoardId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Join Board")
	FOptionalBool bJoinBoard;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};