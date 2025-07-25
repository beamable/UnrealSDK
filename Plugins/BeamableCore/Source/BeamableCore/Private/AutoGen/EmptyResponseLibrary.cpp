
#include "BeamableCore/Public/AutoGen/EmptyResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEmptyResponseLibrary::EmptyResponseToJsonString(const UEmptyResponse* Serializable, const bool Pretty)
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

UEmptyResponse* UEmptyResponseLibrary::Make(FString Result, UObject* Outer)
{
	auto Serializable = NewObject<UEmptyResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UEmptyResponseLibrary::Break(const UEmptyResponse* Serializable, FString& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

