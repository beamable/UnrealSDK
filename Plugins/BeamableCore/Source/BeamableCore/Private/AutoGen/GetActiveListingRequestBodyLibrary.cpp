
#include "BeamableCore/Public/AutoGen/GetActiveListingRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetActiveListingRequestBodyLibrary::GetActiveListingRequestBodyToJsonString(const UGetActiveListingRequestBody* Serializable, const bool Pretty)
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

UGetActiveListingRequestBody* UGetActiveListingRequestBodyLibrary::Make(FString Listing, FOptionalString Store, FOptionalString Time, UObject* Outer)
{
	auto Serializable = NewObject<UGetActiveListingRequestBody>(Outer);
	Serializable->Listing = Listing;
	Serializable->Store = Store;
	Serializable->Time = Time;
	
	return Serializable;
}

void UGetActiveListingRequestBodyLibrary::Break(const UGetActiveListingRequestBody* Serializable, FString& Listing, FOptionalString& Store, FOptionalString& Time)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Listing = Serializable->Listing;
		Store = Serializable->Store;
		Time = Serializable->Time;
	}
		
}

