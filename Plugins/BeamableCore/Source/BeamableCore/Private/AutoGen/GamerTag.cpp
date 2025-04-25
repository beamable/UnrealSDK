
#include "BeamableCore/Public/AutoGen/GamerTag.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGamerTag::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tag"), Tag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("added"), &Added, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionUser*>(TEXT("user"), &User, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCohortEntry*>, UCohortEntry*>(TEXT("trials"), &Trials, Serializer);
}

void UGamerTag::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("tag"), Tag, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("platform"), Platform, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("alias"), &Alias, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("added"), &Added, Serializer);
	UBeamJsonUtils::SerializeOptional<USessionUser*>(TEXT("user"), &User, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UCohortEntry*>, UCohortEntry*>(TEXT("trials"), &Trials, Serializer);		
}

void UGamerTag::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("tag")), Tag);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("platform")), Platform);
	UBeamJsonUtils::DeserializeOptional<FString>("alias", Bag, Alias, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("added", Bag, Added, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<USessionUser*>("user", Bag, User, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UCohortEntry*>, UCohortEntry*>("trials", Bag, Trials, OuterOwner);
}



