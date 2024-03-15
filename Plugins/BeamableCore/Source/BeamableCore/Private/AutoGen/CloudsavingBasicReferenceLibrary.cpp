
#include "BeamableCore/Public/AutoGen/CloudsavingBasicReferenceLibrary.h"

#include "CoreMinimal.h"


FString UCloudsavingBasicReferenceLibrary::CloudsavingBasicReferenceToJsonString(const UCloudsavingBasicReference* Serializable, const bool Pretty)
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

UCloudsavingBasicReference* UCloudsavingBasicReferenceLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UCloudsavingBasicReference>(Outer);
	
	return Serializable;
}



