
#include "BeamableCore/Public/AutoGen/BulkUpdateMailObjectRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBulkUpdateMailObjectRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMyMailUpdate*>(TEXT("updateMailRequests"), UpdateMailRequests, Serializer);
}

void UBulkUpdateMailObjectRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<UMyMailUpdate*>(TEXT("updateMailRequests"), UpdateMailRequests, Serializer);		
}

void UBulkUpdateMailObjectRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<UMyMailUpdate*>(Bag->GetArrayField(TEXT("updateMailRequests")), UpdateMailRequests, OuterOwner);
}



