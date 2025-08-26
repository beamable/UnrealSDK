
#include "BeamableCore/Public/AutoGen/MailSearchResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailSearchResponseLibrary::MailSearchResponseToJsonString(const UMailSearchResponse* Serializable, const bool Pretty)
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

UMailSearchResponse* UMailSearchResponseLibrary::Make(TArray<UMailSearchResponseClause*> Results, UObject* Outer)
{
	auto Serializable = NewObject<UMailSearchResponse>(Outer);
	Serializable->Results = Results;
	
	return Serializable;
}

void UMailSearchResponseLibrary::Break(const UMailSearchResponse* Serializable, TArray<UMailSearchResponseClause*>& Results)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Results = Serializable->Results;
	}
		
}

