
#include "BeamableCore/Public/AutoGen/GetLambdaURILibrary.h"

#include "CoreMinimal.h"
#include "BeamCoreSettings.h"


FString UGetLambdaURILibrary::GetLambdaURIToJsonString(const UGetLambdaURI* Serializable, const bool Pretty)
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

UGetLambdaURI* UGetLambdaURILibrary::Make(FString Uri, UObject* Outer)
{
	auto Serializable = NewObject<UGetLambdaURI>(Outer);
	Serializable->Uri = Uri;
	
	return Serializable;
}

void UGetLambdaURILibrary::Break(const UGetLambdaURI* Serializable, FString& Uri)
{
	if(GetDefault<UBeamCoreSettings>()->BreakGuard(Serializable))
	{
		Uri = Serializable->Uri;
	}
		
}

