
#include "BeamableCore/Public/AutoGen/GroupUpdate.h"
#include "Serialization/BeamJsonUtils.h"




void UGroupUpdate::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("enrollmentType"), &EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("slogan"), &Slogan, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("requirement"), &Requirement, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("motd"), &Motd, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);
}

void UGroupUpdate::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("name"), &Name, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("enrollmentType"), &EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("slogan"), &Slogan, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("requirement"), &Requirement, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("motd"), &Motd, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("subGroup"), &SubGroup, Serializer);		
}

void UGroupUpdate::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<FString>("name", Bag, Name, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("enrollmentType", Bag, EnrollmentType, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("slogan", Bag, Slogan, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("requirement", Bag, Requirement, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("motd", Bag, Motd, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("subGroup", Bag, SubGroup, OuterOwner);
}



