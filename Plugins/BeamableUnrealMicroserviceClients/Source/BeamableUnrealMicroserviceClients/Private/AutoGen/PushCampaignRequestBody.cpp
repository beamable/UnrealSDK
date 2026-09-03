
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/PushCampaignRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UPushCampaignRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("campaignId"), CampaignId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nodeId"), NodeId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cidPid"), CidPid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("campaignData"), CampaignData, Serializer);
	UBeamJsonUtils::SerializeArray<UPushOffer*>(TEXT("offers"), Offers, Serializer);
}

void UPushCampaignRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("title"), Title, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("body"), Body, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("deepLink"), DeepLink, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("campaignId"), CampaignId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("nodeId"), NodeId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("accountId"), AccountId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("cidPid"), CidPid, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("campaignData"), CampaignData, Serializer);
	UBeamJsonUtils::SerializeArray<UPushOffer*>(TEXT("offers"), Offers, Serializer);		
}

void UPushCampaignRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("title"), Bag, Title);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("body"), Bag, Body);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("deepLink"), Bag, DeepLink);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("campaignId"), Bag, CampaignId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("nodeId"), Bag, NodeId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("gamerTag"), Bag, GamerTag);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("accountId"), Bag, AccountId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("cidPid"), Bag, CidPid);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("campaignData"), Bag, CampaignData);
	UBeamJsonUtils::DeserializeArray<UPushOffer*>(TEXT("offers"), Bag, Offers, OuterOwner);
}



