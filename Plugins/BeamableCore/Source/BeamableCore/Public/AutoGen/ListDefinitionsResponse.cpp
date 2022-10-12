
#include "AutoGen/ListDefinitionsResponse.h"
#include "Serialization/BeamJsonUtils.h"


void UListDefinitionsResponse ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementDto*>(TEXT("content"), Content, Serializer);
}

void UListDefinitionsResponse::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UAnnouncementDto*>(TEXT("content"), Content, Serializer);		
}

void UListDefinitionsResponse ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UAnnouncementDto*>(Bag->GetArrayField(TEXT("content")), Content, OuterOwner);
}