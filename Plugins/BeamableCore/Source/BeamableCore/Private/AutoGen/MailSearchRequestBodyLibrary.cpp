
#include "BeamableCore/Public/AutoGen/MailSearchRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailSearchRequestBodyLibrary::MailSearchRequestBodyToJsonString(const UMailSearchRequestBody* Serializable, const bool Pretty)
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

UMailSearchRequestBody* UMailSearchRequestBodyLibrary::Make(TArray<UMailSearchClause*> Clauses, UObject* Outer)
{
	auto Serializable = NewObject<UMailSearchRequestBody>(Outer);
	Serializable->Clauses = Clauses;
	
	return Serializable;
}

void UMailSearchRequestBodyLibrary::Break(const UMailSearchRequestBody* Serializable, TArray<UMailSearchClause*>& Clauses)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Clauses = Serializable->Clauses;
	}
		
}

