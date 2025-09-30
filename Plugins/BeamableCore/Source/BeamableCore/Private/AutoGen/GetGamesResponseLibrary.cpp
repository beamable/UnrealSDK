
#include "BeamableCore/Public/AutoGen/GetGamesResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGamesResponseLibrary::GetGamesResponseToJsonString(const UGetGamesResponse* Serializable, const bool Pretty)
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

UGetGamesResponse* UGetGamesResponseLibrary::Make(FOptionalArrayOfRealmView Realms, UObject* Outer)
{
	auto Serializable = NewObject<UGetGamesResponse>(Outer);
	Serializable->Realms = Realms;
	
	return Serializable;
}

void UGetGamesResponseLibrary::Break(const UGetGamesResponse* Serializable, FOptionalArrayOfRealmView& Realms)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Realms = Serializable->Realms;
	}
		
}

