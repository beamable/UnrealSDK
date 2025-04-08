
#include "BeamableCore/Public/AutoGen/DonationEntry.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UDonationEntry::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("time"), Time);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("claimed"), &bClaimed, Serializer);
}

void UDonationEntry::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("playerId"), PlayerId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("time"), Time);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("claimed"), &bClaimed, Serializer);		
}

void UDonationEntry::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("time")), Time);
	UBeamJsonUtils::DeserializeOptional<bool>("claimed", Bag, bClaimed, OuterOwner);
}



