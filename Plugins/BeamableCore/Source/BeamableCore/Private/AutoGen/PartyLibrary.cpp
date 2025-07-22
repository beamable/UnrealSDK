
#include "BeamableCore/Public/AutoGen/PartyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPartyLibrary::PartyToJsonString(const UParty* Serializable, const bool Pretty)
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

UParty* UPartyLibrary::Make(FOptionalString Id, FOptionalString Restriction, FOptionalBeamGamerTag Leader, FOptionalInt32 MaxSize, FOptionalArrayOfBeamGamerTag Members, FOptionalArrayOfString PendingInvites, UObject* Outer)
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

void UPartyLibrary::Break(const UParty* Serializable, FOptionalString& Id, FOptionalString& Restriction, FOptionalBeamGamerTag& Leader, FOptionalInt32& MaxSize, FOptionalArrayOfBeamGamerTag& Members, FOptionalArrayOfString& PendingInvites)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Id = Serializable->Id;
		Restriction = Serializable->Restriction;
		Leader = Serializable->Leader;
		MaxSize = Serializable->MaxSize;
		Members = Serializable->Members;
		PendingInvites = Serializable->PendingInvites;
	}
		
}

