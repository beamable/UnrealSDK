
#include "AutoGen/DonationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UDonationRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("timeRequested"), TimeRequested);
	UBeamJsonUtils::SerializeArray<UDonationEntry*>(TEXT("progress"), Progress, Serializer);
	Serializer->WriteValue(TEXT("satisfied"), bSatisfied);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeUObject<UCurrency*>("currency", Currency, Serializer);
}

void UDonationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("timeRequested"), TimeRequested);
	UBeamJsonUtils::SerializeArray<UDonationEntry*>(TEXT("progress"), Progress, Serializer);
	Serializer->WriteValue(TEXT("satisfied"), bSatisfied);
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	UBeamJsonUtils::SerializeUObject<UCurrency*>("currency", Currency, Serializer);		
}

void UDonationRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("timeRequested")), TimeRequested);
	UBeamJsonUtils::DeserializeArray<UDonationEntry*>(Bag->GetArrayField(TEXT("progress")), Progress, OuterOwner);
	bSatisfied = Bag->GetBoolField(TEXT("satisfied"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeUObject<UCurrency*>("currency", Bag, Currency, OuterOwner);
}