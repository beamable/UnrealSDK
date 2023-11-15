
#include "BeamableCore/Public/AutoGen/Currency.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrency::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);
}

void UCurrency::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);		
}

void UCurrency::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeOptional<UArchetypeProxy*>("proxy", Bag, Proxy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>("properties", Bag, Properties, OuterOwner);
}



