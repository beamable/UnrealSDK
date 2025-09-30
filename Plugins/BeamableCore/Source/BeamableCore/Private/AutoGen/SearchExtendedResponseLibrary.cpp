
#include "BeamableCore/Public/AutoGen/SearchExtendedResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USearchExtendedResponseLibrary::SearchExtendedResponseToJsonString(const USearchExtendedResponse* Serializable, const bool Pretty)
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

USearchExtendedResponse* USearchExtendedResponseLibrary::Make(TMap<FString, FMapOfString> GamerStats, FOptionalInt32 Offset, FOptionalInt32 Limit, FOptionalInt64 Total, UObject* Outer)
{
	auto Serializable = NewObject<USearchExtendedResponse>(Outer);
	Serializable->GamerStats = GamerStats;
	Serializable->Offset = Offset;
	Serializable->Limit = Limit;
	Serializable->Total = Total;
	
	return Serializable;
}

void USearchExtendedResponseLibrary::Break(const USearchExtendedResponse* Serializable, TMap<FString, FMapOfString>& GamerStats, FOptionalInt32& Offset, FOptionalInt32& Limit, FOptionalInt64& Total)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GamerStats = Serializable->GamerStats;
		Offset = Serializable->Offset;
		Limit = Serializable->Limit;
		Total = Serializable->Total;
	}
		
}

