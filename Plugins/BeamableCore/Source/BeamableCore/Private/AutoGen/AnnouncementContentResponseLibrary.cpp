
#include "BeamableCore/Public/AutoGen/AnnouncementContentResponseLibrary.h"

#include "CoreMinimal.h"


FString UAnnouncementContentResponseLibrary::AnnouncementContentResponseToJsonString(const UAnnouncementContentResponse* Serializable, const bool Pretty)
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

UAnnouncementContentResponse* UAnnouncementContentResponseLibrary::Make(TArray<UAnnouncementContent*> Content, UObject* Outer)
{
	auto Serializable = NewObject<UAnnouncementContentResponse>(Outer);
	Serializable->Content = Content;
	
	return Serializable;
}

void UAnnouncementContentResponseLibrary::Break(const UAnnouncementContentResponse* Serializable, TArray<UAnnouncementContent*>& Content)
{
	Content = Serializable->Content;
		
}

