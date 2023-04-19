
#include "BeamableCore/Public/AutoGen/AccountPersonallyIdentifiableInformationResponse.h"
#include "Serialization/BeamJsonUtils.h"



void UAccountPersonallyIdentifiableInformationResponse::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountPersonallyIdentifiableInformationResponse::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountsBasicAccount*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeUObject<UListAuditResponse*>("paymentAudits", PaymentAudits, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsResponse*>(TEXT("stats"), Stats, Serializer);
}

void UAccountPersonallyIdentifiableInformationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountsBasicAccount*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeUObject<UListAuditResponse*>("paymentAudits", PaymentAudits, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsResponse*>(TEXT("stats"), Stats, Serializer);		
}

void UAccountPersonallyIdentifiableInformationResponse::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UAccountsBasicAccount*>("account", Bag, Account, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UListAuditResponse*>("paymentAudits", Bag, PaymentAudits, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UStatsResponse*>(Bag->GetArrayField(TEXT("stats")), Stats, OuterOwner);
}



