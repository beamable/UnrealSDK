
#include "BeamableCore/Public/AutoGen/GetPlayerStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetPlayerStatusResponseLibrary::GetPlayerStatusResponseToJsonString(const UGetPlayerStatusResponse* Serializable, const bool Pretty)
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

UGetPlayerStatusResponse* UGetPlayerStatusResponseLibrary::Make(TArray<UPlayerStatus*> Statuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetPlayerStatusResponse>(Outer);
	Serializable->Statuses = Statuses;
	
	return Serializable;
}

void UGetPlayerStatusResponseLibrary::Break(const UGetPlayerStatusResponse* Serializable, TArray<UPlayerStatus*>& Statuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Statuses = Serializable->Statuses;
	}
		
}

