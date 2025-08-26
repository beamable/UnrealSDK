
#include "BeamableCore/Public/AutoGen/CreateLaunchMessageRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UCreateLaunchMessageRequestBodyLibrary::CreateLaunchMessageRequestBodyToJsonString(const UCreateLaunchMessageRequestBody* Serializable, const bool Pretty)
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

UCreateLaunchMessageRequestBody* UCreateLaunchMessageRequestBodyLibrary::Make(FString Name, FString Body, UObject* Outer)
{
	auto Serializable = NewObject<UCreateLaunchMessageRequestBody>(Outer);
	Serializable->Name = Name;
	Serializable->Body = Body;
	
	return Serializable;
}

void UCreateLaunchMessageRequestBodyLibrary::Break(const UCreateLaunchMessageRequestBody* Serializable, FString& Name, FString& Body)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Name = Serializable->Name;
		Body = Serializable->Body;
	}
		
}

