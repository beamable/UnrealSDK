
#include "AutoGen/GetManifestRequestBody.h"
#include "Serialization/BeamJsonUtils.h"


void UGetManifestRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);
}

void UGetManifestRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("archived"), &bArchived, Serializer);		
}

void UGetManifestRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Id = Bag->GetStringField(TEXT("id"));
	UBeamJsonUtils::DeserializeOptional<bool>("archived", Bag, bArchived, OuterOwner);
}