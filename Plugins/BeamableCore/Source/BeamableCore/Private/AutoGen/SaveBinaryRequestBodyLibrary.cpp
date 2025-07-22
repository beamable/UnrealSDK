
#include "BeamableCore/Public/AutoGen/SaveBinaryRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveBinaryRequestBodyLibrary::SaveBinaryRequestBodyToJsonString(const USaveBinaryRequestBody* Serializable, const bool Pretty)
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

USaveBinaryRequestBody* USaveBinaryRequestBodyLibrary::Make(TArray<UBinaryDefinition*> Binary, UObject* Outer)
{
	auto Serializable = NewObject<USaveBinaryRequestBody>(Outer);
	Serializable->Binary = Binary;
	
	return Serializable;
}

void USaveBinaryRequestBodyLibrary::Break(const USaveBinaryRequestBody* Serializable, TArray<UBinaryDefinition*>& Binary)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Binary = Serializable->Binary;
	}
		
}

