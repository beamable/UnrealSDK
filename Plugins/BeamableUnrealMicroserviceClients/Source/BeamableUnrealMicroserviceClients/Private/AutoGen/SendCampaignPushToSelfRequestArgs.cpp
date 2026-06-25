
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/SendCampaignPushToSelfRequestArgs.h"
#include "Serialization/BeamJsonUtils.h"




void USendCampaignPushToSelfRequestArgs::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UPushCampaignRequestBody*>("request", Request, Serializer);
}

void USendCampaignPushToSelfRequestArgs::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UPushCampaignRequestBody*>("request", Request, Serializer);		
}

void USendCampaignPushToSelfRequestArgs::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UPushCampaignRequestBody*>("request", Bag, Request, OuterOwner);
}



