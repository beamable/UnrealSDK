
#include "BeamableCore/Public/AutoGen/GetGroupStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGroupStatusResponseLibrary::GetGroupStatusResponseToJsonString(const UGetGroupStatusResponse* Serializable, const bool Pretty)
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

UGetGroupStatusResponse* UGetGroupStatusResponseLibrary::Make(TArray<UGroupStatus*> Statuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetGroupStatusResponse>(Outer);
	Serializable->Statuses = Statuses;
	
	return Serializable;
}

void UGetGroupStatusResponseLibrary::Break(const UGetGroupStatusResponse* Serializable, TArray<UGroupStatus*>& Statuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Statuses = Serializable->Statuses;
	}
		
}

