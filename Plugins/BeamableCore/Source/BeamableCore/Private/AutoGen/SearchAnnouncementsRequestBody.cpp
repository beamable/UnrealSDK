
#include "BeamableCore/Public/AutoGen/SearchAnnouncementsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USearchAnnouncementsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);
}

void USearchAnnouncementsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("date"), &Date, Serializer);		
}

void USearchAnnouncementsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("date", Bag, Date, OuterOwner);
}



