
#include "BeamableCore/Public/AutoGen/MailQueryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailQueryResponseLibrary::MailQueryResponseToJsonString(const UMailQueryResponse* Serializable, const bool Pretty)
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

UMailQueryResponse* UMailQueryResponseLibrary::Make(int64 UnreadCount, UObject* Outer)
{
	auto Serializable = NewObject<UMailQueryResponse>(Outer);
	Serializable->UnreadCount = UnreadCount;
	
	return Serializable;
}

void UMailQueryResponseLibrary::Break(const UMailQueryResponse* Serializable, int64& UnreadCount)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		UnreadCount = Serializable->UnreadCount;
	}
		
}

