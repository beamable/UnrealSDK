
#include "BeamableCore/Public/AutoGen/EventPlayerView.h"
#include "Serialization/BeamJsonUtils.h"



void UEventPlayerView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UEventPlayerView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventPlayerStateView*>(TEXT("running"), Running, Serializer);
	UBeamJsonUtils::SerializeArray<UEventPlayerStateView*>(TEXT("done"), Done, Serializer);
}

void UEventPlayerView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UEventPlayerStateView*>(TEXT("running"), Running, Serializer);
	UBeamJsonUtils::SerializeArray<UEventPlayerStateView*>(TEXT("done"), Done, Serializer);		
}

void UEventPlayerView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UEventPlayerStateView*>(TEXT("running"), Bag, Running, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UEventPlayerStateView*>(TEXT("done"), Bag, Done, OuterOwner);
}



