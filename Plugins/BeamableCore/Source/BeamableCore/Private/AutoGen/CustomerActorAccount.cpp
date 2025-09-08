
#include "BeamableCore/Public/AutoGen/CustomerActorAccount.h"
#include "Serialization/BeamJsonUtils.h"




void UCustomerActorAccount::BeamSerializeProperties(TUnrealJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdTimeMs"), &CreatedTimeMs, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedTimeMs"), &UpdatedTimeMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealmAssociation*>, URealmAssociation*>(TEXT("realmAssociations"), &RealmAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UThirdPartyAssociation*>, UThirdPartyAssociation*>(TEXT("thirdPartyAssociations"), &ThirdPartyAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleAssociation*>, URoleAssociation*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);
}

void UCustomerActorAccount::BeamSerializeProperties(TUnrealPrettyJsonSerializer& Serializer) const
{
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("accountId"), &AccountId, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("createdTimeMs"), &CreatedTimeMs, Serializer);
	UBeamJsonUtils::SerializeOptional<int64>(TEXT("updatedTimeMs"), &UpdatedTimeMs, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("email"), &Email, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("password"), &Password, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("username"), &Username, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("country"), &Country, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("language"), &Language, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("roleString"), &RoleString, Serializer);
	UBeamJsonUtils::SerializeOptional<FString>(TEXT("realmId"), &RealmId, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URealmAssociation*>, URealmAssociation*>(TEXT("realmAssociations"), &RealmAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<UThirdPartyAssociation*>, UThirdPartyAssociation*>(TEXT("thirdPartyAssociations"), &ThirdPartyAssociations, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>(TEXT("external"), &External, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<URoleAssociation*>, URoleAssociation*>(TEXT("roles"), &Roles, Serializer);
	UBeamJsonUtils::SerializeOptional<TArray<FString>, FString>(TEXT("deviceIds"), &DeviceIds, Serializer);		
}

void UCustomerActorAccount::BeamDeserializeProperties(const TSharedPtr<FJsonObject>& Bag)
{
	UBeamJsonUtils::DeserializeOptional<int64>("accountId", Bag, AccountId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("createdTimeMs", Bag, CreatedTimeMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<int64>("updatedTimeMs", Bag, UpdatedTimeMs, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("email", Bag, Email, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("password", Bag, Password, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("username", Bag, Username, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("country", Bag, Country, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("language", Bag, Language, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("roleString", Bag, RoleString, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<FString>("realmId", Bag, RealmId, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URealmAssociation*>, URealmAssociation*>("realmAssociations", Bag, RealmAssociations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<UThirdPartyAssociation*>, UThirdPartyAssociation*>("thirdPartyAssociations", Bag, ThirdPartyAssociations, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FBeamExternalIdentity>, FBeamExternalIdentity>("external", Bag, External, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<URoleAssociation*>, URoleAssociation*>("roles", Bag, Roles, OuterOwner);
	UBeamJsonUtils::DeserializeOptional<TArray<FString>, FString>("deviceIds", Bag, DeviceIds, OuterOwner);
}



