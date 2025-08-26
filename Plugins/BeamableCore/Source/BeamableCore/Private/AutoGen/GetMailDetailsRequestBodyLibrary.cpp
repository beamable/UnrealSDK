
#include "BeamableCore/Public/AutoGen/GetMailDetailsRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetMailDetailsRequestBodyLibrary::GetMailDetailsRequestBodyToJsonString(const UGetMailDetailsRequestBody* Serializable, const bool Pretty)
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

UGetMailDetailsRequestBody* UGetMailDetailsRequestBodyLibrary::Make(int64 Mid, UObject* Outer)
{
	auto Serializable = NewObject<UGetMailDetailsRequestBody>(Outer);
	Serializable->Mid = Mid;
	
	return Serializable;
}

void UGetMailDetailsRequestBodyLibrary::Break(const UGetMailDetailsRequestBody* Serializable, int64& Mid)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Mid = Serializable->Mid;
	}
		
}

