
#include "BeamableCore/Public/AutoGen/EventQueryResponseLibrary.h"

#include "CoreMinimal.h"


FString UEventQueryResponseLibrary::EventQueryResponseToJsonString(const UEventQueryResponse* Serializable, const bool Pretty)
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

UEventQueryResponse* UEventQueryResponseLibrary::Make(TArray<UEventObjectData*> Events, UObject* Outer)
{
	auto Serializable = NewObject<UEventQueryResponse>(Outer);
	Serializable->Events = Events;
	
	return Serializable;
}

void UEventQueryResponseLibrary::Break(const UEventQueryResponse* Serializable, TArray<UEventObjectData*>& Events)
{
	Events = Serializable->Events;
		
}

