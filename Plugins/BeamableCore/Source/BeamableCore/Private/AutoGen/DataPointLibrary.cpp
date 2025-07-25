
#include "BeamableCore/Public/AutoGen/DataPointLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDataPointLibrary::DataPointToJsonString(const UDataPoint* Serializable, const bool Pretty)
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

UDataPoint* UDataPointLibrary::Make(FString Timestamp, FString Value, UObject* Outer)
{
	auto Serializable = NewObject<UDataPoint>(Outer);
	Serializable->Timestamp = Timestamp;
	Serializable->Value = Value;
	
	return Serializable;
}

void UDataPointLibrary::Break(const UDataPoint* Serializable, FString& Timestamp, FString& Value)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Timestamp = Serializable->Timestamp;
		Value = Serializable->Value;
	}
		
}

