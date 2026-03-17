
#include "BeamableCore/Public/AutoGen/AuthV2EmptyMessageLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UAuthV2EmptyMessageLibrary::AuthV2EmptyMessageToJsonString(const UAuthV2EmptyMessage* Serializable, const bool Pretty)
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

UAuthV2EmptyMessage* UAuthV2EmptyMessageLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UAuthV2EmptyMessage>(Outer);
	
	return Serializable;
}



