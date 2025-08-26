
#include "BeamableCore/Public/AutoGen/ClearStatusRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UClearStatusRequestBodyLibrary::ClearStatusRequestBodyToJsonString(const UClearStatusRequestBody* Serializable, const bool Pretty)
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

UClearStatusRequestBody* UClearStatusRequestBodyLibrary::Make(FString Store, UObject* Outer)
{
	auto Serializable = NewObject<UClearStatusRequestBody>(Outer);
	Serializable->Store = Store;
	
	return Serializable;
}

void UClearStatusRequestBodyLibrary::Break(const UClearStatusRequestBody* Serializable, FString& Store)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Store = Serializable->Store;
	}
		
}

