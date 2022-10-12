
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "LeaderboardListResponse.generated.h"

UCLASS(BlueprintType)
class ULeaderboardListResponse : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Total")
	int32 Total;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Offset")
	int32 Offset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Name List")
	TArray<FString> NameList;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};