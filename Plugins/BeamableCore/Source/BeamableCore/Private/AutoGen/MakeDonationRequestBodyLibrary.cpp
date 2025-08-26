
#include "BeamableCore/Public/AutoGen/MakeDonationRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMakeDonationRequestBodyLibrary::MakeDonationRequestBodyToJsonString(const UMakeDonationRequestBody* Serializable, const bool Pretty)
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

UMakeDonationRequestBody* UMakeDonationRequestBodyLibrary::Make(int64 RecipientId, int64 Amount, FOptionalBool bAutoClaim, UObject* Outer)
{
	auto Serializable = NewObject<UMakeDonationRequestBody>(Outer);
	Serializable->RecipientId = RecipientId;
	Serializable->Amount = Amount;
	Serializable->bAutoClaim = bAutoClaim;
	
	return Serializable;
}

void UMakeDonationRequestBodyLibrary::Break(const UMakeDonationRequestBody* Serializable, int64& RecipientId, int64& Amount, FOptionalBool& bAutoClaim)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RecipientId = Serializable->RecipientId;
		Amount = Serializable->Amount;
		bAutoClaim = Serializable->bAutoClaim;
	}
		
}

