
#include "BeamableCore/Public/AutoGen/AccountsObjectAccount.h"
#include "Serialization/BeamJsonUtils.h"
#include "Misc/DefaultValueHelper.h"


void UAccountsObjectAccount::DeserializeRequestResponse(UObject* RequestData, FString ResponseContent)
{
	OuterOwner = RequestData;
	BeamDeserialize(ResponseContent);	
}

void UAccountsObjectAccount::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("privilegedAccount"), bPrivilegedAccount, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdTimeMillis"), CreatedTimeMillis, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updatedTimeMillis"), UpdatedTimeMillis, Serializer);
	UBeamJsonUtils::SerializeArray<UThirdPartyAssociation*>(TEXT("thirdParties"), ThirdParties, Serializer);
	UBeamJsonUtils::SerializeArray<FBeamExternalIdentity>(TEXT("external"), External, Serializer);
	UBeamJsonUtils::SerializeArray<UGamerTagAssociation*>(TEXT("gamerTags"), GamerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("wasMigrated"), &bWasMigrated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);
}

void UAccountsObjectAccount::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("privilegedAccount"), bPrivilegedAccount, Serializer);
	UBeamJsonUtils::SerializeSemanticType<int64>(TEXT("id"), &Id, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("createdTimeMillis"), CreatedTimeMillis, Serializer);
	UBeamJsonUtils::SerializeRawPrimitive(TEXT("updatedTimeMillis"), UpdatedTimeMillis, Serializer);
	UBeamJsonUtils::SerializeArray<UThirdPartyAssociation*>(TEXT("thirdParties"), ThirdParties, Serializer);
	UBeamJsonUtils::SerializeArray<FBeamExternalIdentity>(TEXT("external"), External, Serializer);
	UBeamJsonUtils::SerializeArray<UGamerTagAssociation*>(TEXT("gamerTags"), GamerTags, Serializer);
	UBeamJsonUtils::SerializeOptional<bool>(TEXT("wasMigrated"), &bWasMigrated, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("userName"), &UserName, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("deviceId"), &DeviceId, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("heartbeat"), &Heartbeat, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleMapping*>, URoleMapping*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>(TEXT("inFlight"), &InFlight, Serializer);		
}

void UAccountsObjectAccount::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("privilegedAccount")), bPrivilegedAccount);
	UBeamJsonUtils::DeserializeSemanticType<int64>(Bag->TryGetField(TEXT("id")), Id, OuterOwner);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("createdTimeMillis")), CreatedTimeMillis);
	UBeamJsonUtils::DeserializeRawPrimitive(Bag->GetStringField(TEXT("updatedTimeMillis")), UpdatedTimeMillis);
	UBeamJsonUtils::DeserializeArray<UThirdPartyAssociation*>(Bag->GetArrayField(TEXT("thirdParties")), ThirdParties, OuterOwner);
	UBeamJsonUtils::DeserializeArray<FBeamExternalIdentity>(Bag->GetArrayField(TEXT("external")), External, OuterOwner);
	UBeamJsonUtils::DeserializeArray<UGamerTagAssociation*>(Bag->GetArrayField(TEXT("gamerTags")), GamerTags, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<bool>("wasMigrated", Bag, bWasMigrated, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("userName", Bag, UserName, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("deviceId", Bag, DeviceId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("country", Bag, Country, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("roleString", Bag, RoleString, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("heartbeat", Bag, Heartbeat, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URoleMapping*>, URoleMapping*>("roles", Bag, Roles, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deviceIds", Bag, DeviceIds, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UInFlightMessage*>, UInFlightMessage*>("inFlight", Bag, InFlight, OuterOwner);
}



