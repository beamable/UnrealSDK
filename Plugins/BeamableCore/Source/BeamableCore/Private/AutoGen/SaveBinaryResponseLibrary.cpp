
#include "BeamableCore/Public/AutoGen/SaveBinaryResponseLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString USaveBinaryResponseLibrary::SaveBinaryResponseToJsonString(const USaveBinaryResponse* Serializable, const bool Pretty)
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

USaveBinaryResponse* USaveBinaryResponseLibrary::Make(TArray<UBinaryReference*> Binary, UObject* Outer)
{
	auto Serializable = NewObject<USaveBinaryResponse>(Outer);
	Serializable->Binary = Binary;
	
	return Serializable;
}

void USaveBinaryResponseLibrary::Break(const USaveBinaryResponse* Serializable, TArray<UBinaryReference*>& Binary)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Binary = Serializable->Binary;
	}
		
}

