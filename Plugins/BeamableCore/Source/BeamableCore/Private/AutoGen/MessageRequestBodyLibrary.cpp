
#include "BeamableCore/Public/AutoGen/MessageRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UMessageRequestBodyLibrary::MessageRequestBodyToJsonString(const UMessageRequestBody* Serializable, const bool Pretty)
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

UMessageRequestBody* UMessageRequestBodyLibrary::Make(FOptionalString Body, FOptionalBeamPid Pid, FOptionalBeamGamerTag PlayerId, FOptionalString Channel, FOptionalBeamPid RealmId, UObject* Outer)
{
	auto Serializable = NewObject<UMessageRequestBody>(Outer);
	Serializable->Body = Body;
	Serializable->Pid = Pid;
	Serializable->PlayerId = PlayerId;
	Serializable->Channel = Channel;
	Serializable->RealmId = RealmId;
	
	return Serializable;
}

void UMessageRequestBodyLibrary::Break(const UMessageRequestBody* Serializable, FOptionalString& Body, FOptionalBeamPid& Pid, FOptionalBeamGamerTag& PlayerId, FOptionalString& Channel, FOptionalBeamPid& RealmId)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Body = Serializable->Body;
		Pid = Serializable->Pid;
		PlayerId = Serializable->PlayerId;
		Channel = Serializable->Channel;
		RealmId = Serializable->RealmId;
	}
		
}

