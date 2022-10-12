
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Friend.h"
#include "AutoGen/PlayerId.h"
#include "AutoGen/Invite.h"

#include "Social.generated.h"

UCLASS(BlueprintType)
class USocial : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FString PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Friends")
	TArray<UFriend*> Friends;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Blocked")
	TArray<UPlayerId*> Blocked;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Invites")
	TArray<UInvite*> Invites;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};