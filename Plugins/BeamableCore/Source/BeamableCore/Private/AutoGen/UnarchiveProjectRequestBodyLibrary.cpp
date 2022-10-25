
#include "AutoGen/UnarchiveProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UUnarchiveProjectRequestBodyLibrary::UnarchiveProjectRequestBodyToJsonString(const UUnarchiveProjectRequestBody* Serializable, const bool Pretty)
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

UUnarchiveProjectRequestBody* UUnarchiveProjectRequestBodyLibrary::Make(FString ProjectId, UObject* Outer)
{
	auto Serializable = NewObject<UUnarchiveProjectRequestBody>(Outer);
	Serializable->ProjectId = ProjectId;
	
	return Serializable;
}

void UUnarchiveProjectRequestBodyLibrary::Break(const UUnarchiveProjectRequestBody* Serializable, FString& ProjectId)
{
	ProjectId = Serializable->ProjectId;
		
}

