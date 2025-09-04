
#include "BeamableCore/Public/AutoGen/CustomerActorPromoteRealmRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerActorPromoteRealmRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<EBeamPromotableType>, EBeamPromotableType>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);
}

void UCustomerActorPromoteRealmRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("sourceRealmId"), SourceRealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<EBeamPromotableType>, EBeamPromotableType>(TEXT("promotions"), &Promotions, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("contentManifestIds"), &ContentManifestIds, Serializer);		
}

void UCustomerActorPromoteRealmRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("sourceRealmId"), Bag, SourceRealmId);
	UBeamJsonUtils::DeserializeOptional<TArray<EBeamPromotableType>, EBeamPromotableType>("promotions", Bag, Promotions, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("contentManifestIds", Bag, ContentManifestIds, OuterOwner);
}



