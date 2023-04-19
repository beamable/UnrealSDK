
#include "BeamableCore/Public/AutoGen/MailSearchRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UMailSearchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMailSearchClause*>(TEXT("clauses"), Clauses, Serializer);
}

void UMailSearchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMailSearchClause*>(TEXT("clauses"), Clauses, Serializer);		
}

void UMailSearchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UMailSearchClause*>(Bag->GetArrayField(TEXT("clauses")), Clauses, OuterOwner);
}



