
#include "BeamableCore/Public/AutoGen/ConnectionStringResponseLibrary.h"

#include "CoreMinimal.h"


FString UConnectionStringResponseLibrary::ConnectionStringResponseToJsonString(const UConnectionStringResponse* Serializable, const bool Pretty)
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

UConnectionStringResponse* UConnectionStringResponseLibrary::Make(FOptionalString ConnectionString, UObject* Outer)
{
	auto Serializable = NewObject<UConnectionStringResponse>(Outer);
	Serializable->ConnectionString = ConnectionString;
	
	return Serializable;
}

void UConnectionStringResponseLibrary::Break(const UConnectionStringResponse* Serializable, FOptionalString& ConnectionString)
{
	ConnectionString = Serializable->ConnectionString;
		
}

