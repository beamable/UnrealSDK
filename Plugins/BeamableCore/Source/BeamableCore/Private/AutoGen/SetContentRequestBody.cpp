
#include "BeamableCore/Public/AutoGen/SetContentRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void USetContentRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEvent*>("event", Event, Serializer);
	Serializer->WriteValue(TEXT("origin"), Origin);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);
}

void USetContentRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UEvent*>("event", Event, Serializer);
	Serializer->WriteValue(TEXT("origin"), Origin);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("rootEventId"), &RootEventId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("originType"), &OriginType, Serializer);		
}

void USetContentRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UEvent*>("event", Bag, Event, OuterOwner);
	Origin = Bag->GetStringField(TEXT("origin"));
	UBeamJsonUtils::DeserializeOptional<FString>("rootEventId", Bag, RootEventId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("originType", Bag, OriginType, OuterOwner);
}



