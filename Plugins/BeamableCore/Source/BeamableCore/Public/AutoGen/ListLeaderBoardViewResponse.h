
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/LeaderBoardView.h"

#include "ListLeaderBoardViewResponse.generated.h"

UCLASS(BlueprintType)
class UListLeaderBoardViewResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Result")
	FString Result;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lbs")
	TArray<ULeaderBoardView*> Lbs;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};