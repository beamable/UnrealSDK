
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/GetDeliveryOrdersResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetDeliveryOrdersResultLibrary::GetDeliveryOrdersResultToJsonString(const UGetDeliveryOrdersResult* Serializable, const bool Pretty)
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

UGetDeliveryOrdersResult* UGetDeliveryOrdersResultLibrary::Make(bool bSuccess, FString Message, TArray<UDeliveryOrderInfo*> Orders, UObject* Outer)
{
	auto Serializable = NewObject<UGetDeliveryOrdersResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	Serializable->Orders = Orders;
	
	return Serializable;
}

void UGetDeliveryOrdersResultLibrary::Break(const UGetDeliveryOrdersResult* Serializable, bool& bSuccess, FString& Message, TArray<UDeliveryOrderInfo*>& Orders)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
		Orders = Serializable->Orders;
	}
		
}

