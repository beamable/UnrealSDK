
#include "BeamableCore/Public/AutoGen/RealmsBasicNewGameRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString URealmsBasicNewGameRequestBodyLibrary::RealmsBasicNewGameRequestBodyToJsonString(const URealmsBasicNewGameRequestBody* Serializable, const bool Pretty)
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

URealmsBasicNewGameRequestBody* URealmsBasicNewGameRequestBodyLibrary::Make(FString GameName, UObject* Outer)
{
	auto Serializable = NewObject<URealmsBasicNewGameRequestBody>(Outer);
	Serializable->GameName = GameName;
	
	return Serializable;
}

void URealmsBasicNewGameRequestBodyLibrary::Break(const URealmsBasicNewGameRequestBody* Serializable, FString& GameName)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		GameName = Serializable->GameName;
	}
		
}

