
#include "BeamableCore/Public/AutoGen/ResultResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UResultResponseLibrary::ResultResponseToJsonString(const UResultResponse* Serializable, const bool Pretty)
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

UResultResponse* UResultResponseLibrary::Make(bool bResult, UObject* Outer)
{
	auto Serializable = NewObject<UResultResponse>(Outer);
	Serializable->bResult = bResult;
	
	return Serializable;
}

void UResultResponseLibrary::Break(const UResultResponse* Serializable, bool& bResult)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bResult = Serializable->bResult;
	}
		
}

