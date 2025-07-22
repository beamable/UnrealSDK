
#include "BeamableCore/Public/AutoGen/StartSessionResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStartSessionResponseLibrary::StartSessionResponseToJsonString(const UStartSessionResponse* Serializable, const bool Pretty)
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

UStartSessionResponse* UStartSessionResponseLibrary::Make(FString Result, FOptionalGamerTag Gamer, UObject* Outer)
{
	auto Serializable = NewObject<UStartSessionResponse>(Outer);
	Serializable->Result = Result;
	Serializable->Gamer = Gamer;
	
	return Serializable;
}

void UStartSessionResponseLibrary::Break(const UStartSessionResponse* Serializable, FString& Result, FOptionalGamerTag& Gamer)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		Gamer = Serializable->Gamer;
	}
		
}

