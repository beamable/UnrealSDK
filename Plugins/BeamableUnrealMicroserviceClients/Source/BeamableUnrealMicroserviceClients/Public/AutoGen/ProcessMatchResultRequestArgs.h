#pragma once

#include "CoreMinimal.h"

#include "Serialization/BeamJsonSerializable.h"
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/BeamballTeamInfo.h"
#include "Serialization/BeamJsonUtils.h"

#include "ProcessMatchResultRequestArgs.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLEUNREALMICROSERVICECLIENTS_API UProcessMatchResultRequestArgs : public UObject, public IBeamJsonSerializableUObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Lobby Id", Category="Beam")
	FString LobbyId = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Team Infos", Category="Beam")
	TArray<UBeamballTeamInfo*> TeamInfos = {};

	

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};