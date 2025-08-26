
#include "BeamableCore/Public/AutoGen/EmptyMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UEmptyMessageLibrary::EmptyMessageToJsonString(const UEmptyMessage* Serializable, const bool Pretty)
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

UEmptyMessage* UEmptyMessageLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UEmptyMessage>(Outer);
	
	return Serializable;
}



