
#include "BeamableCore/Public/AutoGen/ListAuditResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UListAuditResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UListAuditResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPaymentAuditEntryViewModel*>(TEXT("audits"), Audits, Serializer);
}

void UListAuditResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UPaymentAuditEntryViewModel*>(TEXT("audits"), Audits, Serializer);		
}

void UListAuditResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UPaymentAuditEntryViewModel*>(Bag->GetArrayField(TEXT("audits")), Audits, OuterOwner);
}



