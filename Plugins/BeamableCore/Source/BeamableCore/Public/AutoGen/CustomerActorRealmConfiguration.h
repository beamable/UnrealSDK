#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
#include "Serialization/BeamJsonUtils.h"
#include "BeamableCore/Public/AutoGen/WebSocketConfiguration.h"

#include "CustomerActorRealmConfiguration.generated.h"

UCLASS(BlueprintType, Category="Beam", DefaultToInstanced, EditInlineNew)
class BEAMABLECORE_API UCustomerActorRealmConfiguration : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Environment", Category="Beam")
	FString Environment = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Websocket Config", Category="Beam")
	UWebSocketConfiguration* WebsocketConfig = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Microservice Uri", Category="Beam")
	FString MicroserviceUri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Microservice Ecr Uri", Category="Beam")
	FString MicroserviceEcrUri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Portal Uri", Category="Beam")
	FString PortalUri = {};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Storage Browser Uri", Category="Beam")
	FString StorageBrowserUri = {};

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};