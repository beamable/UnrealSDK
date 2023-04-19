
#include "BeamableCore/Public/AutoGen/MakeDonationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMakeDonationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("recipientId"), RecipientId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoClaim"), &bAutoClaim, Serializer);
}

void UMakeDonationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("recipientId"), RecipientId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("autoClaim"), &bAutoClaim, Serializer);		
}

void UMakeDonationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("recipientId")), RecipientId);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeOptional<bool>("autoClaim", Bag, bAutoClaim, OuterOwner);
}



