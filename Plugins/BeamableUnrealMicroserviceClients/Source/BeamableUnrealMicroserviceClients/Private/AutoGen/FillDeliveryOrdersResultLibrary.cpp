
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/FillDeliveryOrdersResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFillDeliveryOrdersResultLibrary::FillDeliveryOrdersResultToJsonString(const UFillDeliveryOrdersResult* Serializable, const bool Pretty)
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

UFillDeliveryOrdersResult* UFillDeliveryOrdersResultLibrary::Make(int32 OrdersAdded, bool bSuccess, int32 TotalOrders, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<UFillDeliveryOrdersResult>(Outer);
	Serializable->OrdersAdded = OrdersAdded;
	Serializable->bSuccess = bSuccess;
	Serializable->TotalOrders = TotalOrders;
	Serializable->Message = Message;
	
	return Serializable;
}

void UFillDeliveryOrdersResultLibrary::Break(const UFillDeliveryOrdersResult* Serializable, int32& OrdersAdded, bool& bSuccess, int32& TotalOrders, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OrdersAdded = Serializable->OrdersAdded;
		bSuccess = Serializable->bSuccess;
		TotalOrders = Serializable->TotalOrders;
		Message = Serializable->Message;
	}
		
}

