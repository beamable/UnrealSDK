
#include "BeamableCore/Public/AutoGen/GetManifestDiffsRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGetManifestDiffsRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("manifestId"), &ManifestId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("fromUid"), &FromUid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("toUid"), &ToUid, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("fromDate"), &FromDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("toDate"), &ToDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UGetManifestDiffsRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeSemanticType<FString>(TEXT("manifestId"), &ManifestId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("fromUid"), &FromUid, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("toUid"), &ToUid, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("fromDate"), &FromDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("toDate"), &ToDate, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UGetManifestDiffsRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeSemanticType<FString>(Bag->TryGetField(TEXT("manifestId")), ManifestId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("fromUid", Bag, FromUid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("toUid", Bag, ToUid, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("offset", Bag, Offset, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("fromDate", Bag, FromDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("toDate", Bag, ToDate, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



