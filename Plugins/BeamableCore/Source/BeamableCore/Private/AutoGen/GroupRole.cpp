
#include "BeamableCore/Public/AutoGen/GroupRole.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupRole::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("permissions"), Permissions, Serializer);
}

void UGroupRole::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("name"), Name);
	UBeamJsonUtils::SerializeArray<FString>(TEXT("permissions"), Permissions, Serializer);		
}

void UGroupRole::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	Name = Bag->GetStringField(TEXT("name"));
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("permissions")), Permissions, OuterOwner);
}



