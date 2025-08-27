
#include "BeamableCore/Public/AutoGen/ServicePlansResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServicePlansResponseLibrary::ServicePlansResponseToJsonString(const UServicePlansResponse* Serializable, const bool Pretty)
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

UServicePlansResponse* UServicePlansResponseLibrary::Make(TArray<UServicePlan*> Result, UObject* Outer)
{
	auto Serializable = NewObject<UServicePlansResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UServicePlansResponseLibrary::Break(const UServicePlansResponse* Serializable, TArray<UServicePlan*>& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

