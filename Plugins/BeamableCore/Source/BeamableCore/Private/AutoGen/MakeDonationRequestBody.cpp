
#include "BeamableCore/Public/AutoGen/MakeDonationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMakeDonationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("recipientId"), RecipientId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoClaim"), &bAutoClaim, Serializer);
}

void UMakeDonationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("recipientId"), RecipientId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoClaim"), &bAutoClaim, Serializer);		
}

void UMakeDonationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("recipientId"), Bag, RecipientId);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("amount"), Bag, Amount);
	UBeamJsonUtils::DeserializeOptional<bool>("autoClaim", Bag, bAutoClaim, OuterOwner);
}



