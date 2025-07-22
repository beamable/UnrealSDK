
#include "BeamableCore/Public/AutoGen/GetOffersReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetOffersReqLibrary::GetOffersReqToJsonString(const UGetOffersReq* Serializable, const bool Pretty)
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

UGetOffersReq* UGetOffersReqLibrary::Make(FOptionalString Language, FOptionalString Time, FOptionalString Stores, UObject* Outer)
{
	auto Serializable = NewObject<UGetOffersReq>(Outer);
	Serializable->Language = Language;
	Serializable->Time = Time;
	Serializable->Stores = Stores;
	
	return Serializable;
}

void UGetOffersReqLibrary::Break(const UGetOffersReq* Serializable, FOptionalString& Language, FOptionalString& Time, FOptionalString& Stores)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Language = Serializable->Language;
		Time = Serializable->Time;
		Stores = Serializable->Stores;
	}
		
}

