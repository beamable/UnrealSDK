
#include "AutoGen/GamerTagAssociation.h"

#include "Misc/DefaultValueHelper.h"

void UGamerTagAssociation ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
}

void UGamerTagAssociation::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("projectId"), ProjectId);
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);		
}

void UGamerTagAssociation ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	ProjectId = Bag->GetStringField(TEXT("projectId"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
}