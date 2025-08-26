
#include "BeamableCore/Public/AutoGen/CloudsavingBasicURLResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCloudsavingBasicURLResponseLibrary::CloudsavingBasicURLResponseToJsonString(const UCloudsavingBasicURLResponse* Serializable, const bool Pretty)
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

UCloudsavingBasicURLResponse* UCloudsavingBasicURLResponseLibrary::Make(FString Url, FString ObjectKey, UObject* Outer)
{
	auto Serializable = NewObject<UCloudsavingBasicURLResponse>(Outer);
	Serializable->Url = Url;
	Serializable->ObjectKey = ObjectKey;
	
	return Serializable;
}

void UCloudsavingBasicURLResponseLibrary::Break(const UCloudsavingBasicURLResponse* Serializable, FString& Url, FString& ObjectKey)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Url = Serializable->Url;
		ObjectKey = Serializable->ObjectKey;
	}
		
}

