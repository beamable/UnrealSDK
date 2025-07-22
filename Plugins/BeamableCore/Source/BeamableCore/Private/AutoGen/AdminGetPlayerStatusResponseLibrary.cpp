
#include "BeamableCore/Public/AutoGen/AdminGetPlayerStatusResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAdminGetPlayerStatusResponseLibrary::AdminGetPlayerStatusResponseToJsonString(const UAdminGetPlayerStatusResponse* Serializable, const bool Pretty)
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

UAdminGetPlayerStatusResponse* UAdminGetPlayerStatusResponseLibrary::Make(TArray<UAdminPlayerStatus*> Statuses, UObject* Outer)
{
	auto Serializable = NewObject<UAdminGetPlayerStatusResponse>(Outer);
	Serializable->Statuses = Statuses;
	
	return Serializable;
}

void UAdminGetPlayerStatusResponseLibrary::Break(const UAdminGetPlayerStatusResponse* Serializable, TArray<UAdminPlayerStatus*>& Statuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Statuses = Serializable->Statuses;
	}
		
}

