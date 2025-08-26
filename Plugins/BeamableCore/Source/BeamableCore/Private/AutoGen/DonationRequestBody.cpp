
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
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("satisfied"), Bag, bSatisfied);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("timeRequested"), Bag, TimeRequested);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("playerId"), Bag, PlayerId);
	UBeamJsonUtils::DeserializeUObject<UCurrency*>("currency", Bag, Currency, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UDonationEntry*>(TEXT("progress"), Bag, Progress, OuterOwner);
}



