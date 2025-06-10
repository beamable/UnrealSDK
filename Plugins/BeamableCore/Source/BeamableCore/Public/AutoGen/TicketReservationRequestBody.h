#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamContentId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTag.h"

#include "TicketReservationRequestBody.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTicketReservationRequestBody : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Watch Online Status", Category="Beam")
	FOptionalBool bWatchOnlineStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Wait Duration Secs", Category="Beam")
	FOptionalInt32 MaxWaitDurationSecs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Team", Category="Beam")
	FOptionalString Team = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	FOptionalArrayOfBeamGamerTag Players = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Match Types", Category="Beam")
	FOptionalArrayOfBeamContentId MatchTypes = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfBeamTag Tags = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};