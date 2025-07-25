
#include "BeamableCore/Public/AutoGen/MailSearchResponseClause.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMailSearchResponseClause::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMessage*>, UMessage*>(TEXT("content"), &Content, Serializer);
}

void UMailSearchResponseClause::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("count"), Count, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UMessage*>, UMessage*>(TEXT("content"), &Content, Serializer);		
}

void UMailSearchResponseClause::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("count"), Bag, Count);
	UBeamJsonUtils::DeserializeOptional<TArray<UMessage*>, UMessage*>("content", Bag, Content, OuterOwner);
}



