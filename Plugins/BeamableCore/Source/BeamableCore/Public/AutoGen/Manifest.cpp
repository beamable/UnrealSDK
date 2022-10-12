
#include "AutoGen/Manifest.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"

void UManifest ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UReference*>(TEXT("manifest"), Manifest, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
	Serializer->WriteValue(TEXT("replacement"), bReplacement);
}

void UManifest::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeArray<UReference*>(TEXT("manifest"), Manifest, Serializer);
	Serializer->WriteValue(TEXT("created"), Created);
	Serializer->WriteValue(TEXT("replacement"), bReplacement);		
}

void UManifest ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeArray<UReference*>(Bag->GetArrayField(TEXT("manifest")), Manifest, OuterOwner);
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("created")), Created);
	bReplacement = Bag->GetBoolField(TEXT("replacement"));
}