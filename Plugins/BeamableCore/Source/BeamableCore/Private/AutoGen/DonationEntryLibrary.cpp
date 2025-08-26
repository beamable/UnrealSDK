
#include "BeamableCore/Public/AutoGen/DonationEntryLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDonationEntryLibrary::DonationEntryToJsonString(const UDonationEntry* Serializable, const bool Pretty)
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

UDonationEntry* UDonationEntryLibrary::Make(int64 PlayerId, int64 Amount, int64 Time, FOptionalBool bClaimed, UObject* Outer)
{
	auto Serializable = NewObject<UDonationEntry>(Outer);
	Serializable->PlayerId = PlayerId;
	Serializable->Amount = Amount;
	Serializable->Time = Time;
	Serializable->bClaimed = bClaimed;
	
	return Serializable;
}

void UDonationEntryLibrary::Break(const UDonationEntry* Serializable, int64& PlayerId, int64& Amount, int64& Time, FOptionalBool& bClaimed)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		PlayerId = Serializable->PlayerId;
		Amount = Serializable->Amount;
		Time = Serializable->Time;
		bClaimed = Serializable->bClaimed;
	}
		
}

