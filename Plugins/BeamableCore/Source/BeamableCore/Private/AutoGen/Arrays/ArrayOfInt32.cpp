
#include "BeamableCore/Public/AutoGen/Arrays/ArrayOfInt32.h"
#include "Serialization/BeamJsonUtils.h"

FArrayOfInt32::FArrayOfInt32() = default;

FArrayOfInt32::FArrayOfInt32(const TArray<int32>& Values): Values(Values)
{
}

void FArrayOfInt32::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int32>(Values, Serializer);
}

void FArrayOfInt32::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<int32>(Values, Serializer);
}

void FArrayOfInt32::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
{
	UBeamJsonUtils::DeserializeArray<int32>(Elements, Values);
}
