
#include "BeamableCore/Public/AutoGen/CurrencyView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrencyView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);
}

void UCurrencyView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("amount"), Amount, Serializer);
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<UFederationInfo*>(TEXT("proxy"), &Proxy, Serializer);		
}

void UCurrencyView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeArray<UCurrencyProperty*>(Bag->GetArrayField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UFederationInfo*>("proxy", Bag, Proxy, OuterOwner);
}



