
#include "BeamableCore/Public/AutoGen/GroupCreate.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"



void UGroupCreate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enrollmentType"), EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requirement"), Requirement, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxSize"), MaxSize, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);
}

void UGroupCreate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enrollmentType"), EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requirement"), Requirement, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxSize"), MaxSize, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("time"), &Time, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("group"), &Group, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>(TEXT("scores"), &Scores, Serializer);		
}

void UGroupCreate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enrollmentType"), Bag, EnrollmentType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("requirement"), Bag, Requirement);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("type"), Bag, Type);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("maxSize"), Bag, MaxSize);
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("time", Bag, Time, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("group", Bag, Group, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupScoreBinding*>, UGroupScoreBinding*>("scores", Bag, Scores, OuterOwner);
}



