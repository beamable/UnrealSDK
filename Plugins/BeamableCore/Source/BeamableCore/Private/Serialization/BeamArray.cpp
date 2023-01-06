#include "Serialization/BeamArray.h"

void FBeamArray::BeamSerialize(TUnrealJsonSerializer& Serializer) const
{	
	BeamSerializeProperties(Serializer);	
}

void FBeamArray::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamArray::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	ensure(false);
}

void FBeamArray::BeamDeserialize(const FString& JsonString)
{
	TArray<TSharedPtr<FJsonValue>> Elements;
	const auto ArrayReader = TJsonReaderFactory<>::Create(JsonString);
	FJsonSerializer::Deserialize(ArrayReader, Elements);
	BeamDeserializeElements(Elements);
}

void FBeamArray::BeamDeserializeElements(const TArray<TSharedPtr<FJsonValue>>& Elements)
{
	ensure(false);
}
