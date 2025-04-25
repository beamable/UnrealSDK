
#include "BeamableCore/Public/AutoGen/DonationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UDonationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("satisfied"), bSatisfied, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timeRequested"), TimeRequested, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeUObject<UCurrency*>("currency", Currency, Serializer);
	UBeamJsonUtils::SerializeArray<UDonationEntry*>(TEXT("progress"), Progress, Serializer);
}

void UDonationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("satisfied"), bSatisfied, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("timeRequested"), TimeRequested, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeUObject<UCurrency*>("currency", Currency, Serializer);
	UBeamJsonUtils::SerializeArray<UDonationEntry*>(TEXT("progress"), Progress, Serializer);		
}

void UDonationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("satisfied")), bSatisfied);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("timeRequested")), TimeRequested);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeUObject<UCurrency*>("currency", Bag, Currency, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UDonationEntry*>(Bag->GetArrayField(TEXT("progress")), Progress, OuterOwner);
}



