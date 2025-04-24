
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/MSPlaygroundAddResponseLibrary.h"

#include "CoreMinimal.h"


FString UMSPlaygroundAddResponseLibrary::MSPlaygroundAddResponseToJsonString(const UMSPlaygroundAddResponse* Serializable, const bool Pretty)
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

UMSPlaygroundAddResponse* UMSPlaygroundAddResponseLibrary::Make(int32 Value, UObject* Outer)
{
	auto Serializable = NewObject<UMSPlaygroundAddResponse>(Outer);
	Serializable->Value = Value;
	
	return Serializable;
}

void UMSPlaygroundAddResponseLibrary::Break(const UMSPlaygroundAddResponse* Serializable, int32& Value)
{
	Value = Serializable->Value;
		
}

