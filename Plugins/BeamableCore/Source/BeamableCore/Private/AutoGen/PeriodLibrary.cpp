
#include "BeamableCore/Public/AutoGen/PeriodLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPeriodLibrary::PeriodToJsonString(const UPeriod* Serializable, const bool Pretty)
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

UPeriod* UPeriodLibrary::Make(FString Start, FOptionalString End, UObject* Outer)
{
	auto Serializable = NewObject<UPeriod>(Outer);
	Serializable->Start = Start;
	Serializable->End = End;
	
	return Serializable;
}

void UPeriodLibrary::Break(const UPeriod* Serializable, FString& Start, FOptionalString& End)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Start = Serializable->Start;
		End = Serializable->End;
	}
		
}

