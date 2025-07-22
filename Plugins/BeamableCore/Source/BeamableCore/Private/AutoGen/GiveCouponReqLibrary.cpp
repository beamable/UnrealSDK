
#include "BeamableCore/Public/AutoGen/GiveCouponReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGiveCouponReqLibrary::GiveCouponReqToJsonString(const UGiveCouponReq* Serializable, const bool Pretty)
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

UGiveCouponReq* UGiveCouponReqLibrary::Make(FString Listing, UObject* Outer)
{
	auto Serializable = NewObject<UGiveCouponReq>(Outer);
	Serializable->Listing = Listing;
	
	return Serializable;
}

void UGiveCouponReqLibrary::Break(const UGiveCouponReq* Serializable, FString& Listing)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Listing = Serializable->Listing;
	}
		
}

