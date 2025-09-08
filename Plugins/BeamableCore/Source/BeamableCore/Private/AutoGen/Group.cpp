
#include "BeamableCore/Public/AutoGen/Group.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UGroup::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UGroup::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requirement"), Requirement, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxSize"), MaxSize, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("motd"), Motd, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slogan"), Slogan, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leader"), Leader, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enrollmentType"), EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("freeSlots"), FreeSlots, Serializer);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);
}

void UGroup::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("requirement"), Requirement, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("maxSize"), MaxSize, Serializer);
	Serializer->WriteValue(TEXT("type"), UBeamJsonUtils::EnumToSerializationName(Type));
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("id"), Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("motd"), Motd, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("slogan"), Slogan, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("leader"), Leader, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("created"), Created, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("name"), Name, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("enrollmentType"), EnrollmentType, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("freeSlots"), FreeSlots, Serializer);
	UBeamJsonUtils::SerializeArray<UGroup*>(TEXT("subGroups"), SubGroups, Serializer);
	UBeamJsonUtils::SerializeArray<UMember*>(TEXT("members"), Members, Serializer);
	UBeamJsonUtils::SerializeMap<FString>(TEXT("scores"), Scores, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canDisband"), &bCanDisband, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateEnrollment"), &bCanUpdateEnrollment, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateMOTD"), &bCanUpdateMOTD, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("canUpdateSlogan"), &bCanUpdateSlogan, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("shard"), &Shard, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("clientData"), &ClientData, Serializer);
	UBeamJsonUtils::SerializeOptional<int32>(TEXT("version"), &Version, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("tag"), &Tag, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>(TEXT("donations"), &Donations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupRole*>, UGroupRole*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
	UBeamJsonUtils::SerializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>(TEXT("maybeDonations"), &MaybeDonations, Serializer);		
}

void UGroup::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("requirement"), Bag, Requirement);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("maxSize"), Bag, MaxSize);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("type"), Bag, Type);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("id"), Bag, Id);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("motd"), Bag, Motd);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("slogan"), Bag, Slogan);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("leader"), Bag, Leader);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("created"), Bag, Created);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("name"), Bag, Name);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("enrollmentType"), Bag, EnrollmentType);
	UBeamJsonUtils::DeserializeRawPrimitive(TEXT("freeSlots"), Bag, FreeSlots);
	UBeamJsonUtils::DeserializeArray<UGroup*>(TEXT("subGroups"), Bag, SubGroups, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UMember*>(TEXT("members"), Bag, Members, OuterOwner);
	UBeamJsonUtils::DeserializeMap<FString>(TEXT("scores"), Bag, Scores, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canDisband", Bag, bCanDisband, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateEnrollment", Bag, bCanUpdateEnrollment, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateMOTD", Bag, bCanUpdateMOTD, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("canUpdateSlogan", Bag, bCanUpdateSlogan, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("shard", Bag, Shard, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("clientData", Bag, ClientData, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int32>("version", Bag, Version, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("tag", Bag, Tag, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UDonationRequestBody*>, UDonationRequestBody*>("donations", Bag, Donations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupRole*>, UGroupRole*>("roles", Bag, Roles, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UGroupUsersObjectInFlightMessage*>, UGroupUsersObjectInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TMap<FString, UDonationRequestBody*>, UDonationRequestBody*>("maybeDonations", Bag, MaybeDonations, OuterOwner);
}



