
#include "BeamableCore/Public/AutoGen/ClientPermission.h"





void UClientPermission::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("write_self"), bWriteSelf);
}

void UClientPermission::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("write_self"), bWriteSelf);		
}

void UClientPermission::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	bWriteSelf = Bag->GetBoolField(TEXT("write_self"));
}



