
#include "BeamableUnreal/AutoGen/StandaloneMicroserviceAlwaysTrueRequestArgsLibrary.h"

#include "CoreMinimal.h"


FString UStandaloneMicroserviceAlwaysTrueRequestArgsLibrary::StandaloneMicroserviceAlwaysTrueRequestArgsToJsonString(const UStandaloneMicroserviceAlwaysTrueRequestArgs* Serializable, const bool Pretty)
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

UStandaloneMicroserviceAlwaysTrueRequestArgs* UStandaloneMicroserviceAlwaysTrueRequestArgsLibrary::Make(FString Text, UObject* Outer)
{
	auto Serializable = NewObject<UStandaloneMicroserviceAlwaysTrueRequestArgs>(Outer);
	Serializable->Text = Text;
	
	return Serializable;
}

void UStandaloneMicroserviceAlwaysTrueRequestArgsLibrary::Break(const UStandaloneMicroserviceAlwaysTrueRequestArgs* Serializable, FString& Text)
{
	Text = Serializable->Text;
		
}

