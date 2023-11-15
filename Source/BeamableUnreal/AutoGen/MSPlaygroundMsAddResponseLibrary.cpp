
#include "BeamableUnreal\AutoGen/MSPlaygroundMsAddResponseLibrary.h"

#include "CoreMinimal.h"


FString UMSPlaygroundMsAddResponseLibrary::MSPlaygroundMsAddResponseToJsonString(const UMSPlaygroundMsAddResponse* Serializable, const bool Pretty)
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

UMSPlaygroundMsAddResponse* UMSPlaygroundMsAddResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UMSPlaygroundMsAddResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UMSPlaygroundMsAddResponseLibrary::Break(const UMSPlaygroundMsAddResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

