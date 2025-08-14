
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

USearchExtendedResponse* USearchExtendedResponseLibrary::Make(int32 Offset, int32 Limit, TMap<FString, FMapOfString> GamerStats, FOptionalInt64 Total, UObject* Outer)
{
	auto Serializable = NewObject<USearchExtendedResponse>(Outer);
	Serializable->Offset = Offset;
	Serializable->Limit = Limit;
	Serializable->GamerStats = GamerStats;
	Serializable->Total = Total;
	
	return Serializable;
}

void USearchExtendedResponseLibrary::Break(const USearchExtendedResponse* Serializable, int32& Offset, int32& Limit, TMap<FString, FMapOfString>& GamerStats, FOptionalInt64& Total)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Offset = Serializable->Offset;
		Limit = Serializable->Limit;
		GamerStats = Serializable->GamerStats;
		Total = Serializable->Total;
	}
		
}

