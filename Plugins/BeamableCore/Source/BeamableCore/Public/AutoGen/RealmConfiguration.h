#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "BeamableCore/Public/AutoGen/WebSocketConfiguration.h"
#include "Serialization/BeamJsonUtils.h"

#include "RealmConfiguration.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API URealmConfiguration : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Websocket Config", Category="Beam")
	UWebSocketConfiguration* WebsocketConfig = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Microservice URI", Category="Beam")
	FString MicroserviceURI = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Portal URI", Category="Beam")
	FString PortalURI = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Microservice Ecr URI", Category="Beam")
	FString MicroserviceEcrURI = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Browser URI", Category="Beam")
	FString StorageBrowserURI = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Environment", Category="Beam")
	FString Environment = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};