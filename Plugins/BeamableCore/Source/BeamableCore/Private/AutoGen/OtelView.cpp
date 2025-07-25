
#include "BeamableCore/Public/AutoGen/OtelView.h"
#include "Serialization/BeamJsonUtils.h"



void UOtelView::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UOtelView::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("query"), Query, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isFavorite"), &bIsFavorite, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isPublic"), &bIsPublic, Serializer);
	UBeamJsonUtils::SerializeOptional<UObjectId*>(TEXT("id"), &Id, Serializer);
}

void UOtelView::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("playerId"), PlayerId, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("query"), Query, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isFavorite"), &bIsFavorite, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("isPublic"), &bIsPublic, Serializer);
	UBeamJsonUtils::SerializeOptional<UObjectId*>(TEXT("id"), &Id, Serializer);		
}

void UOtelView::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("playerId")), PlayerId);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("name")), Name);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("query")), Query);
	UBeamJsonUtils::DeserializeOptional<bool>("isFavorite", Bag, bIsFavorite, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("isPublic", Bag, bIsPublic, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<UObjectId*>("id", Bag, Id, OuterOwner);
}



