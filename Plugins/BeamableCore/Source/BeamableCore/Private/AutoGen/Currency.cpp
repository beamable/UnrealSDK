
#include "BeamableCore/Public/AutoGen/Currency.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrency::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);
}

void UCurrency::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedAt"), &UpdatedAt, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>(TEXT("properties"), &Properties, Serializer);		
}

void UCurrency::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeOptional<int64>("updatedAt", Bag, UpdatedAt, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UFederationInfo*>("proxy", Bag, Proxy, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCurrencyProperty*>, UCurrencyProperty*>("properties", Bag, Properties, OuterOwner);
}



