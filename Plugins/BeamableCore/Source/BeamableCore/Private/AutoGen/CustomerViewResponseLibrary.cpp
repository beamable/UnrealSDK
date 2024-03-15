
#include "BeamableCore/Public/AutoGen/CustomerViewResponseLibrary.h"

#include "CoreMinimal.h"


FString UCustomerViewResponseLibrary::CustomerViewResponseToJsonString(const UCustomerViewResponse* Serializable, const bool Pretty)
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

UCustomerViewResponse* UCustomerViewResponseLibrary::Make(UCustomerView* Customer, UObject* Outer)
{
	auto Serializable = NewObject<UCustomerViewResponse>(Outer);
	Serializable->Customer = Customer;
	
	return Serializable;
}

void UCustomerViewResponseLibrary::Break(const UCustomerViewResponse* Serializable, UCustomerView*& Customer)
{
	Customer = Serializable->Customer;
		
}

