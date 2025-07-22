
#include "BeamableCore/Public/AutoGen/PingRspLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UPingRspLibrary::PingRspToJsonString(const UPingRsp* Serializable, const bool Pretty)
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

UPingRsp* UPingRspLibrary::Make(bool bKeepAlive, UObject* Outer)
{
	auto Serializable = NewObject<UPingRsp>(Outer);
	Serializable->bKeepAlive = bKeepAlive;
	
	return Serializable;
}

void UPingRspLibrary::Break(const UPingRsp* Serializable, bool& bKeepAlive)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bKeepAlive = Serializable->bKeepAlive;
	}
		
}

