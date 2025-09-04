
#include "BeamableCore/Public/AutoGen/Realm.h"
#include "Serialization/BeamJsonUtils.h"




void URealm::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isArchived"), &bIsArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("plan"), &Plan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("displayName"), &DisplayName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);
}

void URealm::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isArchived"), &bIsArchived, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("sharded"), &bSharded, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("secret"), &Secret, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("plan"), &Plan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("displayName"), &DisplayName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("parent"), &Parent, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("children"), &Children, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, FString>, FString>(TEXT("config"), &Config, Serializer);		
}

void URealm::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isArchived", Bag, bIsArchived, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("sharded", Bag, bSharded, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("secret", Bag, Secret, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("plan", Bag, Plan, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("displayName", Bag, DisplayName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("parent", Bag, Parent, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("children", Bag, Children, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, FString>, FString>("config", Bag, Config, OuterOwner);
}



