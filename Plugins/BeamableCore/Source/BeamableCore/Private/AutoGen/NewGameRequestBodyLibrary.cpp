
#include "BeamableCore/Public/AutoGen/NewGameRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UNewGameRequestBodyLibrary::NewGameRequestBodyToJsonString(const UNewGameRequestBody* Serializable, const bool Pretty)
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

UNewGameRequestBody* UNewGameRequestBodyLibrary::Make(FString GameName, UObject* Outer)
{
	auto Serializable = NewObject<UNewGameRequestBody>(Outer);
	Serializable->GameName = GameName;
	
	return Serializable;
}

void UNewGameRequestBodyLibrary::Break(const UNewGameRequestBody* Serializable, FString& GameName)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GameName = Serializable->GameName;
	}
		
}

