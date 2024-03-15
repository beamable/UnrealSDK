#pragma once

#include "CoreMinimal.h"
#include "BeamBackend/BeamBaseResponseBodyInterface.h"
#include "Serialization/BeamJsonSerializable.h"
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/OnlineStatusResponses.h
#include "BeamableCore/Public/AutoGen/PlayerOnlineStatusResponse.h"

#include "OnlineStatusResponses.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UOnlineStatusResponses : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
========
#include "BeamableCore/Public/AutoGen/BeamoBasicURLResponse.h"

#include "PreSignedUrlsResponse.generated.h"

UCLASS(BlueprintType, Category="Beam")
class BEAMABLECORE_API UPreSignedUrlsResponse : public UObject, public IBeamJsonSerializableUObject, public IBeamBaseResponseBodyInterface
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h
{
	GENERATED_BODY()

public:
<<<<<<<< HEAD:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/OnlineStatusResponses.h
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Players", Category="Beam")
	TArray<UPlayerOnlineStatusResponse*> Players = {};
========
	UPROPERTY(EditAnywhere, BlueprintReadWrite, DisplayName="Response", Category="Beam")
	TArray<UBeamoBasicURLResponse*> Response = {};
>>>>>>>> main:Plugins/BeamableCore/Source/BeamableCore/Public/AutoGen/PreSignedUrlsResponse.h

	virtual void DeserializeRequestResponse(UObject* RequestData, FString ResponseContent) override;

	virtual void BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const override;
	virtual void BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const override;
	virtual void BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag) override;
	
};