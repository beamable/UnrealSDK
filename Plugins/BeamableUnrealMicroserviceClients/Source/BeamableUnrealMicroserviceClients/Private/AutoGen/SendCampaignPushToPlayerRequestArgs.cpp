
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToPlayerRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void USendCampaignPushToPlayerRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeUObject<UPushCampaignRequestBody*>("request", Request, Serializer);
}

void USendCampaignPushToPlayerRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeUObject<UPushCampaignRequestBody*>("request", Request, Serializer);		
}

void USendCampaignPushToPlayerRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeUObject<UPushCampaignRequestBody*>("request", Bag, Request, OuterOwner);
}



