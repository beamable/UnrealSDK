
#include "BeamableCore/Public/AutoGen/CustomersResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCustomersResponseLibrary::CustomersResponseToJsonString(const UCustomersResponse* Serializable, const bool Pretty)
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

UCustomersResponse* UCustomersResponseLibrary::Make(TArray<UCustomer*> Result, UObject* Outer)
{
	auto Serializable = NewObject<UCustomersResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void UCustomersResponseLibrary::Break(const UCustomersResponse* Serializable, TArray<UCustomer*>& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

