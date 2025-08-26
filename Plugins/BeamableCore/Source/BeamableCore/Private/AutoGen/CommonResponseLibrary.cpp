
#include "BeamableCore/Public/AutoGen/CommonResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCommonResponseLibrary::CommonResponseToJsonString(const UCommonResponse* Serializable, const bool Pretty)
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

UCommonResponse* UCommonResponseLibrary::Make(FString Result, TMap<FString, FString> Data, UObject* Outer)
{
	auto Serializable = NewObject<UCommonResponse>(Outer);
	Serializable->Result = Result;
	Serializable->Data = Data;
	
	return Serializable;
}

void UCommonResponseLibrary::Break(const UCommonResponse* Serializable, FString& Result, TMap<FString, FString>& Data)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
		Data = Serializable->Data;
	}
		
}

