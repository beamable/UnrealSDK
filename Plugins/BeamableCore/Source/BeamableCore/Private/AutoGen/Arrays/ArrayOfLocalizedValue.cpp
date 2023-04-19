
#include "BeamableCore/Public/AutoGen/Arrays/ArrayOfLocalizedValue.h"
#include "Serialization/BeamJsonUtils.h"

FArrayOfLocalizedValue::FArrayOfLocalizedValue() = default;

FArrayOfLocalizedValue::FArrayOfLocalizedValue(const TArray<ULocalizedValue*>& Values): Values(Values)
{
}

void FArrayOfLocalizedValue::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULocalizedValue*>(Values, Serializer);
}

void FArrayOfLocalizedValue::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<ULocalizedValue*>(Values, Serializer);
}

void FArrayOfLocalizedValue::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
{
	UBeamJsonUtils::DeserializeArray<ULocalizedValue*>(Elements, Values);
}
