#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalMapOfDouble.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamTag.h"

#include "Ticket.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UTicket : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Watch Online Status", Category="Beam")
	FOptionalBool bWatchOnlineStatus = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Ticket Id", Category="Beam")
	FOptionalString TicketId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FOptionalString Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Created", Category="Beam")
	FOptionalDateTime Created = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Expires", Category="Beam")
	FOptionalDateTime Expires = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Match Type", Category="Beam")
	FOptionalBeamContentId MatchType = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Match Id", Category="Beam")
	FOptionalString MatchId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Team", Category="Beam")
	FOptionalString Team = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Priority", Category="Beam")
	FOptionalInt32 Priority = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Party Id", Category="Beam")
	FOptionalString PartyId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lobby Id", Category="Beam")
	FOptionalString LobbyId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	FOptionalArrayOfBeamGamerTag Players = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Tags", Category="Beam")
	FOptionalArrayOfBeamTag Tags = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="String Properties", Category="Beam")
	FOptionalMapOfString StringProperties = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Number Properties", Category="Beam")
	FOptionalMapOfDouble NumberProperties = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};