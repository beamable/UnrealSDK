
#include "BeamableCore/Public/AutoGen/DonationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDonationRequestBodyLibrary::DonationRequestBodyToJsonString(const UDonationRequestBody* Serializable, const bool Pretty)
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

UDonationRequestBody* UDonationRequestBodyLibrary::Make(bool bSatisfied, int64 TimeRequested, int64 PlayerId, UCurrency* Currency, TArray<UDonationEntry*> Progress, UObject* Outer)
{
	auto Serializable = NewObject<UDonationRequestBody>(Outer);
	Serializable->bSatisfied = bSatisfied;
	Serializable->TimeRequested = TimeRequested;
	Serializable->PlayerId = PlayerId;
	Serializable->Currency = Currency;
	Serializable->Progress = Progress;
	
	return Serializable;
}

void UDonationRequestBodyLibrary::Break(const UDonationRequestBody* Serializable, bool& bSatisfied, int64& TimeRequested, int64& PlayerId, UCurrency*& Currency, TArray<UDonationEntry*>& Progress)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSatisfied = Serializable->bSatisfied;
		TimeRequested = Serializable->TimeRequested;
		PlayerId = Serializable->PlayerId;
		Currency = Serializable->Currency;
		Progress = Serializable->Progress;
	}
		
}

