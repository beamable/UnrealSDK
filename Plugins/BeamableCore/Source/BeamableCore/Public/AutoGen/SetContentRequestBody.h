
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Event.h"
#include "AutoGen/Optionals/OptionalString.h"

#include "SetContentRequestBody.generated.h"

UCLASS(BlueprintType)
class USetContentRequestBody : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Event")
	UEvent* Event;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin")
	FString Origin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root Event Id")
	FOptionalString RootEventId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin Type")
	FOptionalString OriginType;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};