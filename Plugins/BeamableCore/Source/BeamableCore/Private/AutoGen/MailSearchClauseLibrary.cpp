
#include "BeamableCore/Public/AutoGen/MailSearchClauseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMailSearchClauseLibrary::MailSearchClauseToJsonString(const UMailSearchClause* Serializable, const bool Pretty)
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

UMailSearchClause* UMailSearchClauseLibrary::Make(bool bOnlyCount, FString Name, FOptionalInt64 ForSender, FOptionalInt64 Start, FOptionalInt32 Limit, FOptionalArrayOfString Categories, FOptionalArrayOfString States, UObject* Outer)
{
	auto Serializable = NewObject<UMailSearchClause>(Outer);
	Serializable->bOnlyCount = bOnlyCount;
	Serializable->Name = Name;
	Serializable->ForSender = ForSender;
	Serializable->Start = Start;
	Serializable->Limit = Limit;
	Serializable->Categories = Categories;
	Serializable->States = States;
	
	return Serializable;
}

void UMailSearchClauseLibrary::Break(const UMailSearchClause* Serializable, bool& bOnlyCount, FString& Name, FOptionalInt64& ForSender, FOptionalInt64& Start, FOptionalInt32& Limit, FOptionalArrayOfString& Categories, FOptionalArrayOfString& States)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bOnlyCount = Serializable->bOnlyCount;
		Name = Serializable->Name;
		ForSender = Serializable->ForSender;
		Start = Serializable->Start;
		Limit = Serializable->Limit;
		Categories = Serializable->Categories;
		States = Serializable->States;
	}
		
}

