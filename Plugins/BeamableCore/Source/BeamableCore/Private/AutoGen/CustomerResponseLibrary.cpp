
#include "BeamableCore/Public/AutoGen/CustomerResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomerResponseLibrary::CustomerResponseToJsonString(const UCustomerResponse* Serializable, const bool Pretty)
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

UCustomerResponse* UCustomerResponseLibrary::Make(UCustomer* Customer, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerResponse>(Outer);
	Serializable->Customer = Customer;
	
	return Serializable;
}

void UCustomerResponseLibrary::Break(const UCustomerResponse* Serializable, UCustomer*& Customer)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Customer = Serializable->Customer;
	}
		
}

