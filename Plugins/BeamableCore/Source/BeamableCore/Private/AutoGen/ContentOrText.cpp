
#include "BeamableCore/Public/AutoGen/ContentOrText.h"
#include "Serialization/BeamJsonUtils.h"



void UContentOrText::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UContentOrText::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);
}

void UContentOrText::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("id"), &Id, Serializer);
	Serializer->WriteValue(TEXT("version"), Version);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("properties"), Properties, Serializer);		
}

void UContentOrText::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	Version = Bag->GetStringField(TEXT("version"));
	UBeamJsonUtils::DeserializeMap<FString>(Bag->GetObjectField(TEXT("properties")), Properties, OuterOwner);
}



