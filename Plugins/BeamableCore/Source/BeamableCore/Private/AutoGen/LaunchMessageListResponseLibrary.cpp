
#include "BeamableCore/Public/AutoGen/LaunchMessageListResponseLibrary.h"

#include "CoreMinimal.h"


FString ULaunchMessageListResponseLibrary::LaunchMessageListResponseToJsonString(const ULaunchMessageListResponse* Serializable, const bool Pretty)
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

ULaunchMessageListResponse* ULaunchMessageListResponseLibrary::Make(TArray<FString> Files, UObject* Outer)
{
	auto Serializable = NewObject<ULaunchMessageListResponse>(Outer);
	Serializable->Files = Files;
	
	return Serializable;
}

void ULaunchMessageListResponseLibrary::Break(const ULaunchMessageListResponse* Serializable, TArray<FString>& Files)
{
	Files = Serializable->Files;
		
}

