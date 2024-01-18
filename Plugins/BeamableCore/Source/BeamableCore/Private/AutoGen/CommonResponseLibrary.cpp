
#include "BeamableCore/Public/AutoGen/CommonResponseLibrary.h"

#include "CoreMinimal.h"


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
	Result = Serializable->Result;
	Data = Serializable->Data;
		
}

