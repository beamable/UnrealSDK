
#include "BeamableCore/Public/AutoGen/RealmsBasicCustomersResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicCustomersResponseLibrary::RealmsBasicCustomersResponseToJsonString(const URealmsBasicCustomersResponse* Serializable, const bool Pretty)
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

URealmsBasicCustomersResponse* URealmsBasicCustomersResponseLibrary::Make(TArray<URealmsBasicCustomer*> Result, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicCustomersResponse>(Outer);
	Serializable->Result = Result;
	
	return Serializable;
}

void URealmsBasicCustomersResponseLibrary::Break(const URealmsBasicCustomersResponse* Serializable, TArray<URealmsBasicCustomer*>& Result)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Result = Serializable->Result;
	}
		
}

