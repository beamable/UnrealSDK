
#include "BeamableCore/Public/AutoGen/QueryResponseLibrary.h"

#include "CoreMinimal.h"


FString UQueryResponseLibrary::QueryResponseToJsonString(const UQueryResponse* Serializable, const bool Pretty)
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

UQueryResponse* UQueryResponseLibrary::Make(FOptionalString QueryId, UObject* Outer)
{
	auto Serializable = NewObject<UQueryResponse>(Outer);
	Serializable->QueryId = QueryId;
	
	return Serializable;
}

void UQueryResponseLibrary::Break(const UQueryResponse* Serializable, FOptionalString& QueryId)
{
	QueryId = Serializable->QueryId;
		
}

