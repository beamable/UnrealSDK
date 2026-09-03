
#include "BeamableUnrealMicroserviceClients/Public/AutoGen/RegisterGroundItemResultLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URegisterGroundItemResultLibrary::RegisterGroundItemResultToJsonString(const URegisterGroundItemResult* Serializable, const bool Pretty)
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

URegisterGroundItemResult* URegisterGroundItemResultLibrary::Make(bool bSuccess, FString Message, UObject* Outer)
{
	auto Serializable = NewObject<URegisterGroundItemResult>(Outer);
	Serializable->bSuccess = bSuccess;
	Serializable->Message = Message;
	
	return Serializable;
}

void URegisterGroundItemResultLibrary::Break(const URegisterGroundItemResult* Serializable, bool& bSuccess, FString& Message)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		bSuccess = Serializable->bSuccess;
		Message = Serializable->Message;
	}
		
}

