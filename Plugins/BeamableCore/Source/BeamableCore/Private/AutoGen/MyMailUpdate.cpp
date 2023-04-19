
#include "BeamableCore/Public/AutoGen/MyMailUpdate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UMyMailUpdate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UUpdateMailRequestBody*>("update", Update, Serializer);
}

void UMyMailUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("id"), Id);
	UBeamJsonUtils::SerializeUObject<UUpdateMailRequestBody*>("update", Update, Serializer);		
}

void UMyMailUpdate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("id")), Id);
	UBeamJsonUtils::DeserializeUObject<UUpdateMailRequestBody*>("update", Bag, Update, OuterOwner);
}



