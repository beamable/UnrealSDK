
#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Friend.h"
#include "AutoGen/PlayerId.h"
#include "AutoGen/Invite.h"

#include "Social.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API USocial : public UObject, public FBeamJsonSerializable, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FString PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Friends", Category="Beam")
	TArray<UFriend*> Friends;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Blocked", Category="Beam")
	TArray<UPlayerId*> Blocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invites", Category="Beam")
	TArray<UInvite*> Invites;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};