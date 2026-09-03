
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetPlayerLevelResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetPlayerLevelResultLibrary::GetPlayerLevelResultToJsonString(const UGetPlayerLevelResult* Serializable, const bool Pretty)
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

UGetPlayerLevelResult* UGetPlayerLevelResultLibrary::Make(int32 Level, bool bSuccess, int32 TotalXp, int32 XpForCurrentLevel, int32 XpIntoCurrentLevel, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<UGetPlayerLevelResult>(Outer);
	Serializable->Level = Level;
	Serializable->bSuccess = bSuccess;
	Serializable->TotalXp = TotalXp;
	Serializable->XpForCurrentLevel = XpForCurrentLevel;
	Serializable->XpIntoCurrentLevel = XpIntoCurrentLevel;
	Serializable->Message = Message;
	
	return Serializable;
}

void UGetPlayerLevelResultLibrary::Break(const UGetPlayerLevelResult* Serializable, int32& Level, bool& bSuccess, int32& TotalXp, int32& XpForCurrentLevel, int32& XpIntoCurrentLevel, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Level = Serializable->Level;
		bSuccess = Serializable->bSuccess;
		TotalXp = Serializable->TotalXp;
		XpForCurrentLevel = Serializable->XpForCurrentLevel;
		XpIntoCurrentLevel = Serializable->XpIntoCurrentLevel;
		Message = Serializable->Message;
	}
		
}

