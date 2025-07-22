
#include "BeamableCore/Public/AutoGen/ServiceLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UServiceLimitsLibrary::ServiceLimitsToJsonString(const UServiceLimits* Serializable, const bool Pretty)
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

UServiceLimits* UServiceLimitsLibrary::Make(FOptionalBeamoLimits Beamo, FOptionalContentLimits Content, FOptionalGatewayLimits Gateway, UObject* Outer)
{
	auto Serializable = NewObject<UServiceLimits>(Outer);
	Serializable->Beamo = Beamo;
	Serializable->Content = Content;
	Serializable->Gateway = Gateway;
	
	return Serializable;
}

void UServiceLimitsLibrary::Break(const UServiceLimits* Serializable, FOptionalBeamoLimits& Beamo, FOptionalContentLimits& Content, FOptionalGatewayLimits& Gateway)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Beamo = Serializable->Beamo;
		Content = Serializable->Content;
		Gateway = Serializable->Gateway;
	}
		
}

