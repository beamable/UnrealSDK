
#include "BeamableCore/Public/AutoGen/Currency.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrency::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);
}

void UCurrency::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("amount"), Amount);
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);		
}

void UCurrency::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<int64>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UFederationInfo*>("proxy", Bag, Proxy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>("properties", Bag, Properties, OuterOwner);
}



