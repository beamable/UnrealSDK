
#include "BeamableCore/Public/AutoGen/GetChampionsRequestBodyLibrary.h"

#include "CoreMinimal.h"


FString UGetChampionsRequestBodyLibrary::GetChampionsRequestBodyToJsonString(const UGetChampionsRequestBody* Serializable, const bool Pretty)
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

UGetChampionsRequestBody* UGetChampionsRequestBodyLibrary::Make(FString TournamentId, int32 Cycles, UObject* Outer)
{
	auto Serializable = NewObject<UGetChampionsRequestBody>(Outer);
	Serializable->TournamentId = TournamentId;
	Serializable->Cycles = Cycles;
	
	return Serializable;
}

void UGetChampionsRequestBodyLibrary::Break(const UGetChampionsRequestBody* Serializable, FString& TournamentId, int32& Cycles)
{
	TournamentId = Serializable->TournamentId;
	Cycles = Serializable->Cycles;
		
}

