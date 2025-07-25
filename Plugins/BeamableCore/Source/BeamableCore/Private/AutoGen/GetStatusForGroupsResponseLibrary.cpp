
#include "BeamableCore/Public/AutoGen/GetStatusForGroupsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetStatusForGroupsResponseLibrary::GetStatusForGroupsResponseToJsonString(const UGetStatusForGroupsResponse* Serializable, const bool Pretty)
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

UGetStatusForGroupsResponse* UGetStatusForGroupsResponseLibrary::Make(FString ContentId, TArray<UGroupStatus*> Statuses, UObject* Outer)
{
	auto Serializable = NewObject<UGetStatusForGroupsResponse>(Outer);
	Serializable->ContentId = ContentId;
	Serializable->Statuses = Statuses;
	
	return Serializable;
}

void UGetStatusForGroupsResponseLibrary::Break(const UGetStatusForGroupsResponse* Serializable, FString& ContentId, TArray<UGroupStatus*>& Statuses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ContentId = Serializable->ContentId;
		Statuses = Serializable->Statuses;
	}
		
}

