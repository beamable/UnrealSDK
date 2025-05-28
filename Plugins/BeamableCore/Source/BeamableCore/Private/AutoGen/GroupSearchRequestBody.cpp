
#include "BeamableCore/Public/AutoGen/GroupSearchRequestBody.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupSearchRequestBody::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasSlots"), &bHasSlots, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("subGroup"), &bSubGroup, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("scoreMin"), &ScoreMin, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("sortField"), &SortField, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("userScore"), &UserScore, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("enrollmentTypes"), &EnrollmentTypes, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("scoreMax"), &ScoreMax, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("sortValue"), &SortValue, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);
}

void UGroupSearchRequestBody::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("hasSlots"), &bHasSlots, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("subGroup"), &bSubGroup, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("scoreMin"), &ScoreMin, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("sortField"), &SortField, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("userScore"), &UserScore, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("enrollmentTypes"), &EnrollmentTypes, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("offset"), &Offset, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("scoreMax"), &ScoreMax, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("sortValue"), &SortValue, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("limit"), &Limit, Serializer);		
}

void UGroupSearchRequestBody::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("type")), Type);
	UBeamJsonUtils::DeserializeOptional<bool>("hasSlots", Bag, bHasSlots, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("subGroup", Bag, bSubGroup, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("scoreMin", Bag, ScoreMin, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("sortField", Bag, SortField, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("userScore", Bag, UserScore, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("enrollmentTypes", Bag, EnrollmentTypes, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("offset", Bag, Offset, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("scoreMax", Bag, ScoreMax, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("sortValue", Bag, SortValue, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("limit", Bag, Limit, OuterOwner);
}



