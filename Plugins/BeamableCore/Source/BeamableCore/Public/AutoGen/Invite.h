
#pragma once

#include "CoreMinimal.h"
#include "Serialization/BeamJsonSerializable.h"
#include "AutoGen/Enums/InvitationDirection.h"

#include "Invite.generated.h"

UCLASS(BlueprintType)
class UInvite : public UObject, public FBeamJsonSerializable
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id")
	FString PlayerId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Direction")
	EInvitationDirection Direction;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
};