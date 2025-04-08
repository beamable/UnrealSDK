
#include "BeamableCore/Public/AutoGen/SearchAccountsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void USearchAccountsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("query"), Query);
	Serializer->WriteValue(TEXT("page"), Page);
	Serializer->WriteValue(TEXT("pagesize"), Pagesize);
}

void USearchAccountsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("query"), Query);
	Serializer->WriteValue(TEXT("page"), Page);
	Serializer->WriteValue(TEXT("pagesize"), Pagesize);		
}

void USearchAccountsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("query")), Query);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("page")), Page);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("pagesize")), Pagesize);
}



