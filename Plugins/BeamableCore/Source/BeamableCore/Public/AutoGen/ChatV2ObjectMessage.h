
#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"


#include "ChatV2ObjectMessage.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UChatV2ObjectMessage : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Room Id", Category="Beam")
	FString RoomId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag", Category="Beam")
	int64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timestamp Millis", Category="Beam")
	int64 TimestampMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Censored Content", Category="Beam")
	FString CensoredContent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Id", Category="Beam")
	FGuid MessageId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content", Category="Beam")
	FString Content;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reactions", Category="Beam")
	TMap<FString, FString> Reactions;

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};