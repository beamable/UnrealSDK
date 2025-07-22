
#include "BeamableCore/Public/AutoGen/GatewayLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGatewayLimitsLibrary::GatewayLimitsToJsonString(const UGatewayLimits* Serializable, const bool Pretty)
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

UGatewayLimits* UGatewayLimitsLibrary::Make(int32 MaxConcurrentRequests, UObject* Outer)
{
	auto Serializable = NewObject<UGatewayLimits>(Outer);
	Serializable->MaxConcurrentRequests = MaxConcurrentRequests;
	
	return Serializable;
}

void UGatewayLimitsLibrary::Break(const UGatewayLimits* Serializable, int32& MaxConcurrentRequests)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		MaxConcurrentRequests = Serializable->MaxConcurrentRequests;
	}
		
}

