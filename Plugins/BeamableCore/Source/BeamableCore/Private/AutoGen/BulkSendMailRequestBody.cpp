
#include "BeamableCore/Public/AutoGen/BulkSendMailRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UBulkSendMailRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USendMailRequestBody*>(TEXT("sendMailRequests"), SendMailRequests, Serializer);
}

void UBulkSendMailRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeArray<USendMailRequestBody*>(TEXT("sendMailRequests"), SendMailRequests, Serializer);		
}

void UBulkSendMailRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeArray<USendMailRequestBody*>(Bag->GetArrayField(TEXT("sendMailRequests")), SendMailRequests, OuterOwner);
}



