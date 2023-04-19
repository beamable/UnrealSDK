
#include "BeamableCore/Public/AutoGen/Arrays/ArrayOfCurrencyProperty.h"
#include "Serialization/BeamJsonUtils.h"

FArrayOfCurrencyProperty::FArrayOfCurrencyProperty() = default;

FArrayOfCurrencyProperty::FArrayOfCurrencyProperty(const TArray<UCurrencyProperty*>& Values): Values(Values)
{
}

void FArrayOfCurrencyProperty::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(Values, Serializer);
}

void FArrayOfCurrencyProperty::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UCurrencyProperty*>(Values, Serializer);
}

void FArrayOfCurrencyProperty::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
{
	UBeamJsonUtils::DeserializeArray<UCurrencyProperty*>(Elements, Values);
}
