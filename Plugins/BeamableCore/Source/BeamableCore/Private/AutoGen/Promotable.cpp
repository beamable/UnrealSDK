
#include "BeamableCore/Public/AutoGen/Promotable.h"

#include "Misc/DefaultValueHelper.h"



void UPromotable::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);
}

void UPromotable::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("checksum"), Checksum);
	Serializer->WriteValue(TEXT("createdAt"), CreatedAt);		
}

void UPromotable::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Checksum = Bag->GetStringField(TEXT("checksum"));
	FDefaultValueHelper::ParseInt64(Bag->GetStringField(TEXT("createdAt")), CreatedAt);
}



