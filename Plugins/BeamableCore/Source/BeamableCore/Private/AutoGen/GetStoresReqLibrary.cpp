
#include "BeamableCore/Public/AutoGen/GetStoresReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetStoresReqLibrary::GetStoresReqToJsonString(const UGetStoresReq* Serializable, const bool Pretty)
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

UGetStoresReq* UGetStoresReqLibrary::Make(FOptionalString Scope, UObject* Outer)
{
	auto Serializable = NewObject<UGetStoresReq>(Outer);
	Serializable->Scope = Scope;
	
	return Serializable;
}

void UGetStoresReqLibrary::Break(const UGetStoresReq* Serializable, FOptionalString& Scope)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Scope = Serializable->Scope;
	}
		
}

