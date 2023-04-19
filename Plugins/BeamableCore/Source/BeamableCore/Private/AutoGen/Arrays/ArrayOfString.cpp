
#include "BeamableCore/Public/AutoGen/Arrays/ArrayOfString.h"
#include "Serialization/BeamJsonUtils.h"

FArrayOfString::FArrayOfString() = default;

FArrayOfString::FArrayOfString(const TArray<FString>& Values): Values(Values)
{
}

void FArrayOfString::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(Values, Serializer);
}

void FArrayOfString::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(Values, Serializer);
}

void FArrayOfString::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
{
	UBeamJsonUtils::DeserializeArray<FString>(Elements, Values);
}
