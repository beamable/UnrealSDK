#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBool.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalDateTime.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamGamerTag.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalPresenceStatus.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "OnlineStatus.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UOnlineStatus : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Last Online", Category="Beam")
	FOptionalDateTime LastOnline = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="B Online", Category="Beam")
	FOptionalBool bOnline = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Player Id", Category="Beam")
	FOptionalBeamGamerTag PlayerId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Status", Category="Beam")
	FOptionalPresenceStatus Status = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Description", Category="Beam")
	FOptionalString Description = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};