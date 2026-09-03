
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/DeliverOrderRequestArgsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UDeliverOrderRequestArgsLibrary::DeliverOrderRequestArgsToJsonString(const UDeliverOrderRequestArgs* Serializable, const bool Pretty)
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

UDeliverOrderRequestArgs* UDeliverOrderRequestArgsLibrary::Make(FString OrderId, int64 ItemInstanceId, UObject* Outer)
{
	auto Serializable = NewObject<UDeliverOrderRequestArgs>(Outer);
	Serializable->OrderId = OrderId;
	Serializable->ItemInstanceId = ItemInstanceId;
	
	return Serializable;
}

void UDeliverOrderRequestArgsLibrary::Break(const UDeliverOrderRequestArgs* Serializable, FString& OrderId, int64& ItemInstanceId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OrderId = Serializable->OrderId;
		ItemInstanceId = Serializable->ItemInstanceId;
	}
		
}

