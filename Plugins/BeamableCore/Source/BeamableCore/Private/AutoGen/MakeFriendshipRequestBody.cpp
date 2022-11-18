
#include "AutoGen/MakeFriendshipRequestBody.h"

#include "Misc/DefaultValueHelper.h"



void UMakeFriendshipRequestBody ::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);
}

void UMakeFriendshipRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("gamerTag"), GamerTag);		
}

void UMakeFriendshipRequestBody ::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
}