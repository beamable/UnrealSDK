
#include "BeamableCore/Public/AutoGen/UpdateOtelViewRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UUpdateOtelViewRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isFavorite"), &bIsFavorite, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isPublic"), &bIsPublic, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("query"), &Query, Serializer);
}

void UUpdateOtelViewRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isFavorite"), &bIsFavorite, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isPublic"), &bIsPublic, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("query"), &Query, Serializer);		
}

void UUpdateOtelViewRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<bool>("isFavorite", Bag, bIsFavorite, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("isPublic", Bag, bIsPublic, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("query", Bag, Query, OuterOwner);
}



