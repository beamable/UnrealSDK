
#include "BeamableCore/Public/AutoGen/PartyLibrary.h"

#include "CoreMinimal.h"


FString UPartyLibrary::PartyToJsonString(const UParty* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();			
	}
	return Result;
}	

UParty* UPartyLibrary::Make(FOptionalString Id, FOptionalString Restriction, FOptionalString Leader, FOptionalInt32 MaxSize, FOptionalArrayOfString Members, FOptionalArrayOfString PendingInvites, UObject* Outer)
{
	auto Serializable = NewObject<UParty>(Outer);
	Serializable->Id = Id;
	Serializable->Restriction = Restriction;
	Serializable->Leader = Leader;
	Serializable->MaxSize = MaxSize;
	Serializable->Members = Members;
	Serializable->PendingInvites = PendingInvites;
	
	return Serializable;
}

void UPartyLibrary::Break(const UParty* Serializable, FOptionalString& Id, FOptionalString& Restriction, FOptionalString& Leader, FOptionalInt32& MaxSize, FOptionalArrayOfString& Members, FOptionalArrayOfString& PendingInvites)
{
	Id = Serializable->Id;
	Restriction = Serializable->Restriction;
	Leader = Serializable->Leader;
	MaxSize = Serializable->MaxSize;
	Members = Serializable->Members;
	PendingInvites = Serializable->PendingInvites;
		
}

