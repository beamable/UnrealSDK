
#include "BeamableCore/Public/AutoGen/GetLogsUrlRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetLogsUrlRequestBodyLibrary::GetLogsUrlRequestBodyToJsonString(const UGetLogsUrlRequestBody* Serializable, const bool Pretty)
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

UGetLogsUrlRequestBody* UGetLogsUrlRequestBodyLibrary::Make(FString ServiceName, FOptionalInt64 StartTime, FOptionalString NextToken, FOptionalString Filter, FOptionalInt64 EndTime, FOptionalInt32 Limit, UObject* Outer)
{
	auto Serializable = NewObject<UGetLogsUrlRequestBody>(Outer);
	Serializable->ServiceName = ServiceName;
	Serializable->StartTime = StartTime;
	Serializable->NextToken = NextToken;
	Serializable->Filter = Filter;
	Serializable->EndTime = EndTime;
	Serializable->Limit = Limit;
	
	return Serializable;
}

void UGetLogsUrlRequestBodyLibrary::Break(const UGetLogsUrlRequestBody* Serializable, FString& ServiceName, FOptionalInt64& StartTime, FOptionalString& NextToken, FOptionalString& Filter, FOptionalInt64& EndTime, FOptionalInt32& Limit)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ServiceName = Serializable->ServiceName;
		StartTime = Serializable->StartTime;
		NextToken = Serializable->NextToken;
		Filter = Serializable->Filter;
		EndTime = Serializable->EndTime;
		Limit = Serializable->Limit;
	}
		
}

