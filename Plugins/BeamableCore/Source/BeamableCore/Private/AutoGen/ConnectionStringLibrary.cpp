
#include "BeamableCore/Public/AutoGen/ConnectionStringLibrary.h"

#include "CoreMinimal.h"


FString UConnectionStringLibrary::ConnectionStringToJsonString(const UConnectionString* Serializable, const bool Pretty)
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

UConnectionString* UConnectionStringLibrary::Make(FString ConnectionString, UObject* Outer)
{
	auto Serializable = NewObject<UConnectionString>(Outer);
	Serializable->ConnectionString = ConnectionString;
	
	return Serializable;
}

void UConnectionStringLibrary::Break(const UConnectionString* Serializable, FString& ConnectionString)
{
	ConnectionString = Serializable->ConnectionString;
		
}

