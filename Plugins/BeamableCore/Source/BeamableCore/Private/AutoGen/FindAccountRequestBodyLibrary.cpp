
#include "BeamableCore/Public/AutoGen/FindAccountRequestBodyLibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UFindAccountRequestBodyLibrary::FindAccountRequestBodyToJsonString(const UFindAccountRequestBody* Serializable, const bool Pretty)
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

UFindAccountRequestBody* UFindAccountRequestBodyLibrary::Make(FString Query, UObject* Outer)
{
	auto Serializable = NewObject<UFindAccountRequestBody>(Outer);
	Serializable->Query = Query;
	
	return Serializable;
}

void UFindAccountRequestBodyLibrary::Break(const UFindAccountRequestBody* Serializable, FString& Query)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Query = Serializable->Query;
	}
		
}

