
#include "BeamableCore/Public/AutoGen/ListTagsResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UListTagsResponseLibrary::ListTagsResponseToJsonString(const UListTagsResponse* Serializable, const bool Pretty)
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

UListTagsResponse* UListTagsResponseLibrary::Make(TArray<FString> Tags, UObject* Outer)
{
	auto Serializable = NewObject<UListTagsResponse>(Outer);
	Serializable->Tags = Tags;
	
	return Serializable;
}

void UListTagsResponseLibrary::Break(const UListTagsResponse* Serializable, TArray<FString>& Tags)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Tags = Serializable->Tags;
	}
		
}

