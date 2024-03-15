
#include "BeamableCore/Public/AutoGen/FacebookUpdatedEntryLibrary.h"

#include "CoreMinimal.h"


FString UFacebookUpdatedEntryLibrary::FacebookUpdatedEntryToJsonString(const UFacebookUpdatedEntry* Serializable, const bool Pretty)
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

UFacebookUpdatedEntry* UFacebookUpdatedEntryLibrary::Make(FString Id, int64 Time, TArray<FString> ChangedFields, UObject* Outer)
{
	auto Serializable = NewObject<UFacebookUpdatedEntry>(Outer);
	Serializable->Id = Id;
	Serializable->Time = Time;
	Serializable->ChangedFields = ChangedFields;
	
	return Serializable;
}

void UFacebookUpdatedEntryLibrary::Break(const UFacebookUpdatedEntry* Serializable, FString& Id, int64& Time, TArray<FString>& ChangedFields)
{
	Id = Serializable->Id;
	Time = Serializable->Time;
	ChangedFields = Serializable->ChangedFields;
		
}

