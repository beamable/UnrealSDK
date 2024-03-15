
#include "BeamableCore/Public/AutoGen/RenameProjectRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString URenameProjectRequestBodyLibrary::RenameProjectRequestBodyToJsonString(const URenameProjectRequestBody* Serializable, const bool Pretty)
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

URenameProjectRequestBody* URenameProjectRequestBodyLibrary::Make(FBeamPid ProjectId, FString NewName, UObject* Outer)
{
	auto Serializable = NewObject<URenameProjectRequestBody>(Outer);
	Serializable->ProjectId = ProjectId;
	Serializable->NewName = NewName;
	
	return Serializable;
}

void URenameProjectRequestBodyLibrary::Break(const URenameProjectRequestBody* Serializable, FBeamPid& ProjectId, FString& NewName)
{
	ProjectId = Serializable->ProjectId;
	NewName = Serializable->NewName;
		
}

