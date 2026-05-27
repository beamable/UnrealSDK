
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/StartResearchResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UStartResearchResultLibrary::StartResearchResultToJsonString(const UStartResearchResult* Serializable, const bool Pretty)
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

UStartResearchResult* UStartResearchResultLibrary::Make(int64 StartedAtUtcSeconds, int32 PointsSpent, FString Message, bool bSuccess, UObject* Outer)
{
	auto Serializable = NewObject<UStartResearchResult>(Outer);
	Serializable->StartedAtUtcSeconds = StartedAtUtcSeconds;
	Serializable->PointsSpent = PointsSpent;
	Serializable->Message = Message;
	Serializable->bSuccess = bSuccess;
	
	return Serializable;
}

void UStartResearchResultLibrary::Break(const UStartResearchResult* Serializable, int64& StartedAtUtcSeconds, int32& PointsSpent, FString& Message, bool& bSuccess)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		StartedAtUtcSeconds = Serializable->StartedAtUtcSeconds;
		PointsSpent = Serializable->PointsSpent;
		Message = Serializable->Message;
		bSuccess = Serializable->bSuccess;
	}
		
}

