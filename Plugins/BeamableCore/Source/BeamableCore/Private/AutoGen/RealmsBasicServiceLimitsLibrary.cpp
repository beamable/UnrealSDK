
#include "BeamableCore/Public/AutoGen/RealmsBasicServiceLimitsLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicServiceLimitsLibrary::RealmsBasicServiceLimitsToJsonString(const URealmsBasicServiceLimits* Serializable, const bool Pretty)
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

URealmsBasicServiceLimits* URealmsBasicServiceLimitsLibrary::Make(FOptionalRealmsBasicBeamoLimits Beamo, FOptionalContentLimits Content, FOptionalGatewayLimits Gateway, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicServiceLimits>(Outer);
	Serializable->Beamo = Beamo;
	Serializable->Content = Content;
	Serializable->Gateway = Gateway;
	
	return Serializable;
}

void URealmsBasicServiceLimitsLibrary::Break(const URealmsBasicServiceLimits* Serializable, FOptionalRealmsBasicBeamoLimits& Beamo, FOptionalContentLimits& Content, FOptionalGatewayLimits& Gateway)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Beamo = Serializable->Beamo;
		Content = Serializable->Content;
		Gateway = Serializable->Gateway;
	}
		
}

