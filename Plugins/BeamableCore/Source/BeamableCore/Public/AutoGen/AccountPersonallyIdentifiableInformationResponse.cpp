
#include "AutoGen/AccountPersonallyIdentifiableInformationResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UAccountPersonallyIdentifiableInformationResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountsBasicAccount*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsResponse*>(TEXT("stats"), Stats, Serializer);
	UBeamJsonUtils::SerializeUObject<UListAuditResponse*>("paymentAudits", PaymentAudits, Serializer);
}

void UAccountPersonallyIdentifiableInformationResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeUObject<UAccountsBasicAccount*>("account", Account, Serializer);
	UBeamJsonUtils::SerializeArray<UStatsResponse*>(TEXT("stats"), Stats, Serializer);
	UBeamJsonUtils::SerializeUObject<UListAuditResponse*>("paymentAudits", PaymentAudits, Serializer);		
}

void UAccountPersonallyIdentifiableInformationResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeUObject<UAccountsBasicAccount*>("account", Bag, Account, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UStatsResponse*>(Bag->GetArrayField(TEXT("stats")), Stats, OuterOwner);
	UBeamJsonUtils::DeserializeUObject<UListAuditResponse*>("paymentAudits", Bag, PaymentAudits, OuterOwner);
}