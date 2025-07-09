
#include "BeamableCore/Public/AutoGen/ServiceComponentLibrary.h"

#include "CoreMinimal.h"


FString UServiceComponentLibrary::ServiceComponentToJsonString(const UServiceComponent* Serializable, const bool Pretty)
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

UServiceComponent* UServiceComponentLibrary::Make(FOptionalString Name, UObject* Outer)
{
	auto Serializable = NewObject<UServiceComponent>(Outer);
	Serializable->Name = Name;
	
	return Serializable;
}

void UServiceComponentLibrary::Break(const UServiceComponent* Serializable, FOptionalString& Name)
{
	Name = Serializable->Name;
		
}

