
#include "BeamableCore/Public/AutoGen/GroupRole.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupRole::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("permissions"), Permissions, Serializer);
}

void UGroupRole::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("permissions"), Permissions, Serializer);		
}

void UGroupRole::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeArray<FString>(TEXT("permissions"), Bag, Permissions, OuterOwner);
}



