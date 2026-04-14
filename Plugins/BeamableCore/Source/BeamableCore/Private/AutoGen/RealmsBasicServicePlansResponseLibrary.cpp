
#include "BeamableCore/Public/AutoGen/RealmsBasicServicePlansResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicServicePlansResponseLibrary::RealmsBasicServicePlansResponseToJsonString(const URealmsBasicServicePlansResponse* Serializable, const bool Pretty)
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

URealmsBasicServicePlansResponse* URealmsBasicServicePlansResponseLibrary::Make(TArray<URealmsBasicServicePlan*> Result, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicServicePlansResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void URealmsBasicServicePlansResponseLibrary::Break(const URealmsBasicServicePlansResponse* Serializable, TArray<URealmsBasicServicePlan*>& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

