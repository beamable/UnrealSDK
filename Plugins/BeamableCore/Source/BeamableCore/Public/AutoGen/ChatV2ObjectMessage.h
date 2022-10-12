
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"


#include "ChatV2ObjectMessage.generated.h"

UCLASS(BlueprintType)
class UChatV2ObjectMessage : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Room Id")
	FString RoomId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Gamer Tag")
	int64 GamerTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Reactions")
	TMap<FString, FString> Reactions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Timestamp Millis")
	int64 TimestampMillis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Censored Content")
	FString CensoredContent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Message Id")
	FGuid MessageId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Content")
	FString Content;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};