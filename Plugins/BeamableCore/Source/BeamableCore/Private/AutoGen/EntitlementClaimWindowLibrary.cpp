
#include "BeamableCore/Public/AutoGen/EntitlementClaimWindowLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEntitlementClaimWindowLibrary::EntitlementClaimWindowToJsonString(const UEntitlementClaimWindow* Serializable, const bool Pretty)
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

UEntitlementClaimWindow* UEntitlementClaimWindowLibrary::Make(int64 Open, int64 Close, UObject* Outer)
{
	auto Serializable = NewObject<UEntitlementClaimWindow>(Outer);
	Serializable->Open = Open;
	Serializable->Close = Close;
	
	return Serializable;
}

void UEntitlementClaimWindowLibrary::Break(const UEntitlementClaimWindow* Serializable, int64& Open, int64& Close)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Open = Serializable->Open;
		Close = Serializable->Close;
	}
		
}

