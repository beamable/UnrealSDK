
#include "AutoGen/Manifest.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UManifest ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("replacement"), bReplacement);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UReference*>(TEXT("manifest"), Manifest, Serializer);
}

void UManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("replacement"), bReplacement);
	Serializer->WriteValue(TEXT("id"), Id);
	Serializer->WriteValue(TEXT("created"), Created);
	UBeamJsonUtils::SerializeArray<UReference*>(TEXT("manifest"), Manifest, Serializer);		
}

void UManifest ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bReplacement = Bag->GetBoolField(TEXT("replacement"));
	Id = Bag->GetStringField(TEXT("id"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	UBeamJsonUtils::DeserializeArray<UReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
}