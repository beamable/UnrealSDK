
#include "BeamableCore/Public/AutoGen/GetGameRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetGameRequestBodyLibrary::GetGameRequestBodyToJsonString(const UGetGameRequestBody* Serializable, const bool Pretty)
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

UGetGameRequestBody* UGetGameRequestBodyLibrary::Make(FBeamPid RootPID, UObject* Outer)
{
	auto Serializable = NewObject<UGetGameRequestBody>(Outer);
	Serializable->RootPID = RootPID;
	
	return Serializable;
}

void UGetGameRequestBodyLibrary::Break(const UGetGameRequestBody* Serializable, FBeamPid& RootPID)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		RootPID = Serializable->RootPID;
	}
		
}

