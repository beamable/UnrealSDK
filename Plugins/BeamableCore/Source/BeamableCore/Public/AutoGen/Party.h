#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfString.h"

#include "Party.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UParty : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalString Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Restriction", Category="Beam")
	FOptionalString Restriction = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Leader", Category="Beam")
	FOptionalBeamGamerTag Leader = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Size", Category="Beam")
	FOptionalInt32 MaxSize = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Members", Category="Beam")
	FOptionalArrayOfBeamGamerTag Members = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Pending Invites", Category="Beam")
	FOptionalArrayOfString PendingInvites = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};