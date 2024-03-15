
#include "BeamableCore/Public/AutoGen/StatRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UStatRequestBodyLibrary::StatRequestBodyToJsonString(const UStatRequestBody* Serializable, const bool Pretty)
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

UStatRequestBody* UStatRequestBodyLibrary::Make(FOptionalString Stats, UObject* Outer)
{
	auto Serializable = NewObject<UStatRequestBody>(Outer);
	Serializable->Stats = Stats;
	
	return Serializable;
}

void UStatRequestBodyLibrary::Break(const UStatRequestBody* Serializable, FOptionalString& Stats)
{
	Stats = Serializable->Stats;
		
}

