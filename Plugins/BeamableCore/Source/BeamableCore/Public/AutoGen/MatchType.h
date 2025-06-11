#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalBeamContentId.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalArrayOfTeamContentProto.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalInt32.h"
#include "BeamableCore/Public/AutoGen/Optionals/OptionalString.h"

#include "MatchType.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UMatchType : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Id", Category="Beam")
	FOptionalBeamContentId Id = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Wait After Min Reached Secs", Category="Beam")
	FOptionalInt32 WaitAfterMinReachedSecs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Max Wait Duration Secs", Category="Beam")
	FOptionalInt32 MaxWaitDurationSecs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Matching Interval Secs", Category="Beam")
	FOptionalInt32 MatchingIntervalSecs = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Federated Game Server Namespace", Category="Beam")
	FOptionalString FederatedGameServerNamespace = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Teams", Category="Beam")
	FOptionalArrayOfTeamContentProto Teams = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};