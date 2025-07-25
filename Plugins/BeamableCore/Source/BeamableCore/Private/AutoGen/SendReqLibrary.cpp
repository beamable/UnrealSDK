
#include "BeamableCore/Public/AutoGen/SendReqLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USendReqLibrary::SendReqToJsonString(const USendReq* Serializable, const bool Pretty)
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

USendReq* USendReqLibrary::Make(TArray<USendMsg*> Msgs, UObject* Outer)
{
	auto Serializable = NewObject<USendReq>(Outer);
	Serializable->Msgs = Msgs;
	
	return Serializable;
}

void USendReqLibrary::Break(const USendReq* Serializable, TArray<USendMsg*>& Msgs)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Msgs = Serializable->Msgs;
	}
		
}

