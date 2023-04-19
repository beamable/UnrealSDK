
#include "BeamableCore/Public/AutoGen/CreateProjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCreateProjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("plan"), &Plan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
}

void UCreateProjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("plan"), &Plan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);		
}

void UCreateProjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("plan", Bag, Plan, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
}



