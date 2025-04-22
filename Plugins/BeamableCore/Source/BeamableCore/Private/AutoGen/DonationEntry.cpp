
#include "BeamableCore/Public/AutoGen/DonationEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UDonationEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("claimed"), &bClaimed, Serializer);
}

void UDonationEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("time"), Time, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("claimed"), &bClaimed, Serializer);		
}

void UDonationEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("time")), Time);
	UBeamJsonUtils::DeserializeOptional<bool>("claimed", Bag, bClaimed, OuterOwner);
}



