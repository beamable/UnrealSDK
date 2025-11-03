
#include "BeamableCore/Public/AutoGen/GroupLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGroupLibrary::GroupToJsonString(const UGroup* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<TCHAR>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UGroup* UGroupLibrary::Make(int64 Requirement, int32 MaxSize, EBeamGroupType Type, int64 Id, FString Motd, FString Slogan, int64 Leader, int64 Created, FString Name, FString EnrollmentType, int32 FreeSlots, TArray<UGroup*> SubGroups, TArray<UMember*> Members, TMap<FString, FString> Scores, FOptionalBool bCanDisband, FOptionalBool bCanUpdateEnrollment, FOptionalBool bCanUpdateMOTD, FOptionalBool bCanUpdateSlogan, FOptionalString Shard, FOptionalString ClientData, FOptionalInt32 Version, FOptionalString Tag, FOptionalArrayOfDonationRequestBody Donations, FOptionalArrayOfGroupRole Roles, FOptionalArrayOfInFlightMessage InFlight, FOptionalMapOfDonationRequestBody MaybeDonations, UObject* Outer)
{
	auto Serializable = NewObject<UGroup>(Outer);
	Serializable->Requirement = Requirement;
	Serializable->MaxSize = MaxSize;
	Serializable->Type = Type;
	Serializable->Id = Id;
	Serializable->Motd = Motd;
	Serializable->Slogan = Slogan;
	Serializable->Leader = Leader;
	Serializable->Created = Created;
	Serializable->Name = Name;
	Serializable->EnrollmentType = EnrollmentType;
	Serializable->FreeSlots = FreeSlots;
	Serializable->SubGroups = SubGroups;
	Serializable->Members = Members;
	Serializable->Scores = Scores;
	Serializable->bCanDisband = bCanDisband;
	Serializable->bCanUpdateEnrollment = bCanUpdateEnrollment;
	Serializable->bCanUpdateMOTD = bCanUpdateMOTD;
	Serializable->bCanUpdateSlogan = bCanUpdateSlogan;
	Serializable->Shard = Shard;
	Serializable->ClientData = ClientData;
	Serializable->Version = Version;
	Serializable->Tag = Tag;
	Serializable->Donations = Donations;
	Serializable->Roles = Roles;
	Serializable->InFlight = InFlight;
	Serializable->MaybeDonations = MaybeDonations;
	
	return Serializable;
}

void UGroupLibrary::Break(const UGroup* Serializable, int64& Requirement, int32& MaxSize, EBeamGroupType& Type, int64& Id, FString& Motd, FString& Slogan, int64& Leader, int64& Created, FString& Name, FString& EnrollmentType, int32& FreeSlots, TArray<UGroup*>& SubGroups, TArray<UMember*>& Members, TMap<FString, FString>& Scores, FOptionalBool& bCanDisband, FOptionalBool& bCanUpdateEnrollment, FOptionalBool& bCanUpdateMOTD, FOptionalBool& bCanUpdateSlogan, FOptionalString& Shard, FOptionalString& ClientData, FOptionalInt32& Version, FOptionalString& Tag, FOptionalArrayOfDonationRequestBody& Donations, FOptionalArrayOfGroupRole& Roles, FOptionalArrayOfInFlightMessage& InFlight, FOptionalMapOfDonationRequestBody& MaybeDonations)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Requirement = Serializable->Requirement;
		MaxSize = Serializable->MaxSize;
		Type = Serializable->Type;
		Id = Serializable->Id;
		Motd = Serializable->Motd;
		Slogan = Serializable->Slogan;
		Leader = Serializable->Leader;
		Created = Serializable->Created;
		Name = Serializable->Name;
		EnrollmentType = Serializable->EnrollmentType;
		FreeSlots = Serializable->FreeSlots;
		SubGroups = Serializable->SubGroups;
		Members = Serializable->Members;
		Scores = Serializable->Scores;
		bCanDisband = Serializable->bCanDisband;
		bCanUpdateEnrollment = Serializable->bCanUpdateEnrollment;
		bCanUpdateMOTD = Serializable->bCanUpdateMOTD;
		bCanUpdateSlogan = Serializable->bCanUpdateSlogan;
		Shard = Serializable->Shard;
		ClientData = Serializable->ClientData;
		Version = Serializable->Version;
		Tag = Serializable->Tag;
		Donations = Serializable->Donations;
		Roles = Serializable->Roles;
		InFlight = Serializable->InFlight;
		MaybeDonations = Serializable->MaybeDonations;
	}
		
}

