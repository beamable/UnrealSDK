
#include "BeamableCore/Public/AutoGen/SessionLanguageContextLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionLanguageContextLibrary::SessionLanguageContextToJsonString(const USessionLanguageContext* Serializable, const bool Pretty)
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

USessionLanguageContext* USessionLanguageContextLibrary::Make(FString Code, FString Ctx, UObject* Outer)
{
	auto Serializable = NewObject<USessionLanguageContext>(Outer);
	Serializable->Code = Code;
	Serializable->Ctx = Ctx;
	
	return Serializable;
}

void USessionLanguageContextLibrary::Break(const USessionLanguageContext* Serializable, FString& Code, FString& Ctx)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Code = Serializable->Code;
		Ctx = Serializable->Ctx;
	}
		
}

