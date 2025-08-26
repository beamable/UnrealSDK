
#include "BeamableCore/Public/AutoGen/UpdateListingCooldownRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UUpdateListingCooldownRequestBodyLibrary::UpdateListingCooldownRequestBodyToJsonString(const UUpdateListingCooldownRequestBody* Serializable, const bool Pretty)
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

UUpdateListingCooldownRequestBody* UUpdateListingCooldownRequestBodyLibrary::Make(FString Symbol, int32 CooldownReduction, UObject* Outer)
{
	auto Serializable = NewObject<UUpdateListingCooldownRequestBody>(Outer);
	Serializable->Symbol = Symbol;
	Serializable->CooldownReduction = CooldownReduction;
	
	return Serializable;
}

void UUpdateListingCooldownRequestBodyLibrary::Break(const UUpdateListingCooldownRequestBody* Serializable, FString& Symbol, int32& CooldownReduction)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Symbol = Serializable->Symbol;
		CooldownReduction = Serializable->CooldownReduction;
	}
		
}

