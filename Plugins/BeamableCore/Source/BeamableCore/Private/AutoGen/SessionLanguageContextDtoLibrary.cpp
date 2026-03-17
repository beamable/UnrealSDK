
#include "BeamableCore/Public/AutoGen/SessionLanguageContextDtoLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USessionLanguageContextDtoLibrary::SessionLanguageContextDtoToJsonString(const USessionLanguageContextDto* Serializable, const bool Pretty)
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

USessionLanguageContextDto* USessionLanguageContextDtoLibrary::Make(FOptionalString Code, FOptionalString Ctx, UObject* Outer)
{
	auto Serializable = NewObject<USessionLanguageContextDto>(Outer);
	Serializable->Code = Code;
	Serializable->Ctx = Ctx;
	
	return Serializable;
}

void USessionLanguageContextDtoLibrary::Break(const USessionLanguageContextDto* Serializable, FOptionalString& Code, FOptionalString& Ctx)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Code = Serializable->Code;
		Ctx = Serializable->Ctx;
	}
		
}

