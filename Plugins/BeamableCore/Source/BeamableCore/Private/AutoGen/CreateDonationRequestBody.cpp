
#include "BeamableCore/Public/AutoGen/CreateDonationRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCreateDonationRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currencyId"), CurrencyId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("config"), &Config, Serializer);
}

void UCreateDonationRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("currencyId"), CurrencyId);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("config"), &Config, Serializer);		
}

void UCreateDonationRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	CurrencyId = Bag->GetStringField(TEXT("currencyId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeOptional<FString>("config", Bag, Config, OuterOwner);
}



