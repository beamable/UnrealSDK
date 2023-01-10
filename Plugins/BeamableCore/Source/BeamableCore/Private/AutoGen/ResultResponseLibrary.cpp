
#include "AutoGen/ResultResponseLibrary.h"

#include "CoreMinimal.h"


FString UResultResponseLibrary::ResultResponseToJsonString(const UResultResponse* Serializable, const bool Pretty)
{
	FString Result = FString{};
	if(Pretty)
	{
		TUnrealPrettyJsonSerializer JsonSerializer = TJsonStringWriter<TPrettyJsonPrintPolicy<wchar_t>>::Create(&Result);
		Serializable->BeamSerialize(JsonSerializer);
		JsonSerializer->Close();
	}
	else
	{
		TUnrealJsonSerializer JsonSerializer = TJsonStringWriter<TCondensedJsonPrintPolicy<wchar_t>>::Create(&Result);
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
	bResult = Serializable->bResult;
		
}
