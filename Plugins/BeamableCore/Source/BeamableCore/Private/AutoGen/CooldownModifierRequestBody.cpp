
#include "BeamableCore/Public/AutoGen/CooldownModifierRequestBody.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UCooldownModifierRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<UUpdateListingCooldownRequestBody*>(TEXT("updateListingCooldownRequests"), UpdateListingCooldownRequests, Serializer);
}

void UCooldownModifierRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("gamerTag"), GamerTag, Serializer);
	UBeamJsonUtils::SerializeArray<UUpdateListingCooldownRequestBody*>(TEXT("updateListingCooldownRequests"), UpdateListingCooldownRequests, Serializer);		
}

void UCooldownModifierRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("gamerTag")), GamerTag);
	UBeamJsonUtils::DeserializeArray<UUpdateListingCooldownRequestBody*>(Bag->GetArrayField(TEXT("updateListingCooldownRequests")), UpdateListingCooldownRequests, OuterOwner);
}



