
#include "AutoGen/ChatV2ObjectMessageLibrary.h"

#include "CoreMinimal.h"


FString UChatV2ObjectMessageLibrary::ChatV2ObjectMessageToJsonString(const UChatV2ObjectMessage* Serializable, const bool Pretty)
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

UChatV2ObjectMessage* UChatV2ObjectMessageLibrary::Make(FString RoomId, int64 GamerTag, int64 TimestampMillis, FString CensoredContent, FGuid MessageId, FString Content, TMap<FString, FString> Reactions, UObject* Outer)
{
	auto Serializable = NewObject<UChatV2ObjectMessage>(Outer);
	Serializable->RoomId = RoomId;
	Serializable->GamerTag = GamerTag;
	Serializable->TimestampMillis = TimestampMillis;
	Serializable->CensoredContent = CensoredContent;
	Serializable->MessageId = MessageId;
	Serializable->Content = Content;
	Serializable->Reactions = Reactions;
	
	return Serializable;
}

void UChatV2ObjectMessageLibrary::Break(const UChatV2ObjectMessage* Serializable, FString& RoomId, int64& GamerTag, int64& TimestampMillis, FString& CensoredContent, FGuid& MessageId, FString& Content, TMap<FString, FString>& Reactions)
{
	RoomId = Serializable->RoomId;
	GamerTag = Serializable->GamerTag;
	TimestampMillis = Serializable->TimestampMillis;
	CensoredContent = Serializable->CensoredContent;
	MessageId = Serializable->MessageId;
	Content = Serializable->Content;
	Reactions = Serializable->Reactions;
		
}

