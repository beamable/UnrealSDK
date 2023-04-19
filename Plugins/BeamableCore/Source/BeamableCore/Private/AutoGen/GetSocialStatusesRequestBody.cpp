
#include "BeamableCore/Public/AutoGen/GetSocialStatusesRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetSocialStatusesRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("playerIds"), PlayerIds, Serializer);
}

void UGetSocialStatusesRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<FString>(TEXT("playerIds"), PlayerIds, Serializer);		
}

void UGetSocialStatusesRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<FString>(Bag->GetArrayField(TEXT("playerIds")), PlayerIds, OuterOwner);
}



