#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"


<<<<<<<< HEAD:Source/BeamableUnreal/AutoGen/MSPlaygroundMsAddResponse.h
#include "MSPlaygroundMsAddResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLEUNREAL_API UMSPlaygroundMsAddResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
========
#include "ApiLobbiesServerPostLobbyResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UApiLobbiesServerPostLobbyResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h
{
	GENERATED_BODY()

public:
<<<<<<<< HEAD:Source/BeamableUnreal/AutoGen/MSPlaygroundMsAddResponse.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Value", Category="Beam")
	int32 Value = {};
========
	
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/ApiLobbiesServerPostLobbyResponse.h

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};