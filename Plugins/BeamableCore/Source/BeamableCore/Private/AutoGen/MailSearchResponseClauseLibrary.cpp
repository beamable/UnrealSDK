
#include "BeamableCore/Public/AutoGen/MailSearchResponseClauseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailSearchResponseClauseLibrary::MailSearchResponseClauseToJsonString(const UMailSearchResponseClause* Serializable, const bool Pretty)
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

UMailSearchResponseClause* UMailSearchResponseClauseLibrary::Make(FString Name, int64 Count, FOptionalArrayOfMessage Content, UObject* Outer)
{
	auto Serializable = NewObject<UMailSearchResponseClause>(Outer);
	Serializable->Name = Name;
	Serializable->Count = Count;
	Serializable->Content = Content;
	
	return Serializable;
}

void UMailSearchResponseClauseLibrary::Break(const UMailSearchResponseClause* Serializable, FString& Name, int64& Count, FOptionalArrayOfMessage& Content)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Count = Serializable->Count;
		Content = Serializable->Content;
	}
		
}

