
#include "AutoGen/ArchiveProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UArchiveProjectRequestBodyLibrary::ArchiveProjectRequestBodyToJsonString(const UArchiveProjectRequestBody* Serializable, const bool Pretty)
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

UArchiveProjectRequestBody* UArchiveProjectRequestBodyLibrary::Make(FString Pid, UObject* Outer)
{
	auto Serializable = NewObject<UArchiveProjectRequestBody>(Outer);
	Serializable->Pid = Pid;
	
	return Serializable;
}

void UArchiveProjectRequestBodyLibrary::Break(const UArchiveProjectRequestBody* Serializable, FString& Pid)
{
	Pid = Serializable->Pid;
		
}

