
#include "BeamableCore/Public/AutoGen/GetTotalCouponResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetTotalCouponResponseLibrary::GetTotalCouponResponseToJsonString(const UGetTotalCouponResponse* Serializable, const bool Pretty)
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

UGetTotalCouponResponse* UGetTotalCouponResponseLibrary::Make(int64 Count, UObject* Outer)
{
	auto Serializable = NewObject<UGetTotalCouponResponse>(Outer);
	Serializable->Count = Count;
	
	return Serializable;
}

void UGetTotalCouponResponseLibrary::Break(const UGetTotalCouponResponse* Serializable, int64& Count)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Count = Serializable->Count;
	}
		
}

