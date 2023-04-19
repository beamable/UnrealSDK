
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAnnouncementContentResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAnnouncementContentResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementContent*>(TEXT("content"), Content, Serializer);
}

void UAnnouncementContentResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementContent*>(TEXT("content"), Content, Serializer);		
}

void UAnnouncementContentResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAnnouncementContent*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}



