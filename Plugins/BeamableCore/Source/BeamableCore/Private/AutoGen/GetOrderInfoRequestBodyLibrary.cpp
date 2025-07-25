
#include "BeamableCore/Public/AutoGen/GetOrderInfoRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetOrderInfoRequestBodyLibrary::GetOrderInfoRequestBodyToJsonString(const UGetOrderInfoRequestBody* Serializable, const bool Pretty)
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

UGetOrderInfoRequestBody* UGetOrderInfoRequestBodyLibrary::Make(FString OrderId, UObject* Outer)
{
	auto Serializable = NewObject<UGetOrderInfoRequestBody>(Outer);
	Serializable->OrderId = OrderId;
	
	return Serializable;
}

void UGetOrderInfoRequestBodyLibrary::Break(const UGetOrderInfoRequestBody* Serializable, FString& OrderId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		OrderId = Serializable->OrderId;
	}
		
}

