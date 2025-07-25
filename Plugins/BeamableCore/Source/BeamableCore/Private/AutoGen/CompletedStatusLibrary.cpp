
#include "BeamableCore/Public/AutoGen/CompletedStatusLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCompletedStatusLibrary::CompletedStatusToJsonString(const UCompletedStatus* Serializable, const bool Pretty)
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

UCompletedStatus* UCompletedStatusLibrary::Make(int32 Cycle, int32 Tier, int32 Stage, int32 Delta, UObject* Outer)
{
	auto Serializable = NewObject<UCompletedStatus>(Outer);
	Serializable->Cycle = Cycle;
	Serializable->Tier = Tier;
	Serializable->Stage = Stage;
	Serializable->Delta = Delta;
	
	return Serializable;
}

void UCompletedStatusLibrary::Break(const UCompletedStatus* Serializable, int32& Cycle, int32& Tier, int32& Stage, int32& Delta)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Cycle = Serializable->Cycle;
		Tier = Serializable->Tier;
		Stage = Serializable->Stage;
		Delta = Serializable->Delta;
	}
		
}

