#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Event.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "SetContentRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USetContentRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Event", Category="Beam")
	UEvent* Event = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin", Category="Beam")
	FString Origin = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Root Event Id", Category="Beam")
	FOptionalString RootEventId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Origin Type", Category="Beam")
	FOptionalString OriginType = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};