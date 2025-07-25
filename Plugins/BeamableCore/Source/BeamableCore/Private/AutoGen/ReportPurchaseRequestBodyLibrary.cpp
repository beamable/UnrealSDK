
#include "BeamableCore/Public/AutoGen/ReportPurchaseRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UReportPurchaseRequestBodyLibrary::ReportPurchaseRequestBodyToJsonString(const UReportPurchaseRequestBody* Serializable, const bool Pretty)
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

UReportPurchaseRequestBody* UReportPurchaseRequestBodyLibrary::Make(FString ListingId, FOptionalBool bFree, UObject* Outer)
{
	auto Serializable = NewObject<UReportPurchaseRequestBody>(Outer);
	Serializable->ListingId = ListingId;
	Serializable->bFree = bFree;
	
	return Serializable;
}

void UReportPurchaseRequestBodyLibrary::Break(const UReportPurchaseRequestBody* Serializable, FString& ListingId, FOptionalBool& bFree)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ListingId = Serializable->ListingId;
		bFree = Serializable->bFree;
	}
		
}

