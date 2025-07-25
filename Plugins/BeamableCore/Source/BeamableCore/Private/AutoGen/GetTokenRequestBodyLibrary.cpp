
#include "BeamableCore/Public/AutoGen/GetTokenRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetTokenRequestBodyLibrary::GetTokenRequestBodyToJsonString(const UGetTokenRequestBody* Serializable, const bool Pretty)
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

UGetTokenRequestBody* UGetTokenRequestBodyLibrary::Make(FString Token, UObject* Outer)
{
	auto Serializable = NewObject<UGetTokenRequestBody>(Outer);
	Serializable->Token = Token;
	
	return Serializable;
}

void UGetTokenRequestBodyLibrary::Break(const UGetTokenRequestBody* Serializable, FString& Token)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Token = Serializable->Token;
	}
		
}

