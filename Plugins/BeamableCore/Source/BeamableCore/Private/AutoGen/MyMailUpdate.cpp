
#include "BeamableCore/Public/AutoGen/MyMailUpdate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMyMailUpdate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UUpdateMailRequestBody*>("update", Update, Serializer);
}

void UMyMailUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeUObject<UUpdateMailRequestBody*>("update", Update, Serializer);		
}

void UMyMailUpdate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UUpdateMailRequestBody*>("update", Bag, Update, OuterOwner);
}



