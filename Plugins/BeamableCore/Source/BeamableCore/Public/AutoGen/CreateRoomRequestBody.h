
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "CreateRoomRequestBody.generated.h"

UCLASS(BlueprintType)
class UCreateRoomRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Room Name")
	FString RoomName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Keep Subscribed")
	bool bKeepSubscribed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players")
	TArray<int64> Players;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};