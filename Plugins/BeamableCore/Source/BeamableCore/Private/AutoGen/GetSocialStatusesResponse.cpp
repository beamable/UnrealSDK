
#include "BeamableCore/Public/AutoGen/GetSocialStatusesResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UGetSocialStatusesResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGetSocialStatusesResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USocial*>(TEXT("statuses"), Statuses, Serializer);
}

void UGetSocialStatusesResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USocial*>(TEXT("statuses"), Statuses, Serializer);		
}

void UGetSocialStatusesResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<USocial*>(Bag->GetArrayField(TEXT("statuses")), Statuses, OuterOwner);
}



