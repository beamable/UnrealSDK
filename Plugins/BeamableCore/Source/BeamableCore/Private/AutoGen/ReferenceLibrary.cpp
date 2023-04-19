
#include "BeamableCore/Public/AutoGen/ReferenceLibrary.h"

#include "CoreMinimal.h"


FString UReferenceLibrary::ReferenceToJsonString(const UReference* Serializable, const bool Pretty)
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

UReference* UReferenceLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UReference>(Outer);
	
	return Serializable;
}



