
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "CreateRoomRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UCreateRoomRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Keep Subscribed", Category="Beam")
	bool bKeepSubscribed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Room Name", Category="Beam")
	FString RoomName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	TArray<int64> Players;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};