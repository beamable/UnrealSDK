
#include "BeamableCore/Public/AutoGen/CustomerActorCustomersResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerActorCustomersResponseLibrary::CustomerActorCustomersResponseToJsonString(const UCustomerActorCustomersResponse* Serializable, const bool Pretty)
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

UCustomerActorCustomersResponse* UCustomerActorCustomersResponseLibrary::Make(FOptionalArrayOfCustomerActorCustomer Customers, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerActorCustomersResponse>(Outer);
	Serializable->Customers = Customers;
	
	return Serializable;
}

void UCustomerActorCustomersResponseLibrary::Break(const UCustomerActorCustomersResponse* Serializable, FOptionalArrayOfCustomerActorCustomer& Customers)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Customers = Serializable->Customers;
	}
		
}

