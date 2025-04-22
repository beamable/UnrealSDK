
#include "BeamableCore/Public/AutoGen/SearchAccountsRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void USearchAccountsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("query"), Query, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("page"), Page, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pagesize"), Pagesize, Serializer);
}

void USearchAccountsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("query"), Query, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("page"), Page, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("pagesize"), Pagesize, Serializer);		
}

void USearchAccountsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("query")), Query);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("page")), Page);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("pagesize")), Pagesize);
}



