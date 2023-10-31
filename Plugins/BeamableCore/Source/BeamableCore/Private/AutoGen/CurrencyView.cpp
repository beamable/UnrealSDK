
#include "BeamableCore/Public/AutoGen/CurrencyView.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCurrencyView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("proxy"), &Proxy, Serializer);
}

void UCurrencyView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("amount"), Amount);
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(TEXT("properties"), Properties, Serializer);
	UBeamJsonUtils::SerializeOptional<UArchetypeProxy*>(TEXT("proxy"), &Proxy, Serializer);		
}

void UCurrencyView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("amount")), Amount);
	UBeamJsonUtils::DeserializeArray<UCurrencyProperty*>(Bag->GetArrayField(TEXT("properties")), Properties, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UArchetypeProxy*>("proxy", Bag, Proxy, OuterOwner);
}



