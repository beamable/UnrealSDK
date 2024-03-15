
#include "BeamableCore/Public/AutoGen/RemoveLaunchMessageRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString URemoveLaunchMessageRequestBodyLibrary::RemoveLaunchMessageRequestBodyToJsonString(const URemoveLaunchMessageRequestBody* Serializable, const bool Pretty)
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

URemoveLaunchMessageRequestBody* URemoveLaunchMessageRequestBodyLibrary::Make(FString File, UObject* Outer)
{
	auto Serializable = NewObject<URemoveLaunchMessageRequestBody>(Outer);
	Serializable->File = File;
	
	return Serializable;
}

void URemoveLaunchMessageRequestBodyLibrary::Break(const URemoveLaunchMessageRequestBody* Serializable, FString& File)
{
	File = Serializable->File;
		
}

