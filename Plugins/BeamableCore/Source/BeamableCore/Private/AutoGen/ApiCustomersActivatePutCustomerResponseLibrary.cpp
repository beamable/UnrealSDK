
#include "BeamableCore/Public/AutoGen/ApiCustomersActivatePutCustomerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UApiCustomersActivatePutCustomerResponseLibrary::ApiCustomersActivatePutCustomerResponseToJsonString(const UApiCustomersActivatePutCustomerResponse* Serializable, const bool Pretty)
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

UApiCustomersActivatePutCustomerResponse* UApiCustomersActivatePutCustomerResponseLibrary::Make(UObject* Outer)
{
	auto Serializable = NewObject<UApiCustomersActivatePutCustomerResponse>(Outer);
	
	return Serializable;
}



