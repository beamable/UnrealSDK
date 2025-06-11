#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamBackend/SemanticTypes/BeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Friend.h"
#include "BeamableCore/Public/AutoGen/PlayerId.h"
#include "BeamableCore/Public/AutoGen/Invite.h"

#include "Social.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API USocial : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FBeamGamerTag PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Friends", Category="Beam")
	TArray<UFriend*> Friends = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Blocked", Category="Beam")
	TArray<UPlayerId*> Blocked = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invites", Category="Beam")
	TArray<UInvite*> Invites = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};