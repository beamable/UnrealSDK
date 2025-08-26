
#include "BeamableCore/Public/AutoGen/ObjectRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UObjectRequestBodyLibrary::ObjectRequestBodyToJsonString(const UObjectRequestBody* Serializable, const bool Pretty)
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

UObjectRequestBody* UObjectRequestBodyLibrary::Make(FString ObjectKey, UObject* Outer)
{
	auto Serializable = NewObject<UObjectRequestBody>(Outer);
	Serializable->ObjectKey = ObjectKey;
	
	return Serializable;
}

void UObjectRequestBodyLibrary::Break(const UObjectRequestBody* Serializable, FString& ObjectKey)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		ObjectKey = Serializable->ObjectKey;
	}
		
}

