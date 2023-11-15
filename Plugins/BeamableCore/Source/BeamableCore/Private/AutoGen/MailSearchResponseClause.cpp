
#include "BeamableCore/Public/AutoGen/MailSearchResponseClause.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMailSearchResponseClause::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("count"), Count);
	UBeamJsonUtils::SerializeOptional<TArray<UMessage*>, UMessage*>(TEXT("content"), &Content, Serializer);
}

void UMailSearchResponseClause::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	Serializer->WriteValue(TEXT("count"), Count);
	UBeamJsonUtils::SerializeOptional<TArray<UMessage*>, UMessage*>(TEXT("content"), &Content, Serializer);		
}

void UMailSearchResponseClause::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("count")), Count);
	UBeamJsonUtils::DeserializeOptional<TArray<UMessage*>, UMessage*>("content", Bag, Content, OuterOwner);
}



